#include "GameEngine/GameEngine.h"
#include "GameEngine/Player.h"
#include "Common/Constants.h"
#include "UserInterface/MainWindow.h"
#include "Network/PacketWriter.h"
#include "GameEngine/Bullet.h"
#include "GameEngine/Bonus.h"

#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QVector>
#include <QTimer>

Player::Player(GameEngine* parent, bool isRed, bool isHost) :
    QGraphicsPixmapItem(),
    mGameEngine(parent),
    mUsername(),
    mIsRed(isRed),
    mIsEnemy(isRed == isHost),
    mMovingTimer(new QTimer()),
    mSpeedBonusTimer(new QTimer()),
    mStep(PLAYER_DEFAULT_STEP),
    mPressedKeys(),
    mOrientation(isRed ? Qt::Key_Left : Qt::Key_Right),
    mHasBulletCooldown(false),
    mLives(PLAYER_DEFAULT_LIVES),
    mExtraDamageBuletsNumber(0)
{
    setTransformOriginPoint(15, 30);
    QObject::connect(mMovingTimer, &QTimer::timeout, [=]
    {
        move();
    });

    mSpeedBonusTimer->setSingleShot(true);
    QObject::connect(mSpeedBonusTimer, &QTimer::timeout, [=]
    {
        mStep = PLAYER_DEFAULT_STEP;
    });

    if (isRed)
    {
        setPixmap(QPixmap(":/img/img/car_enemy.png"));
        setPos(PLAYER_ENEMY_START_X, PLAYER_ENEMY_START_Y);
        setRotation(-90);

        if (!isHost)
        {
            setFlag(QGraphicsItem::ItemIsFocusable);
        }
    }
    else
    {
        setPixmap(QPixmap(":/img/img/car.png"));
        setPos(PLAYER_ME_START_X, PLAYER_ME_START_Y);
        setRotation(90);

        if (isHost)
        {
            setFlag(QGraphicsItem::ItemIsFocusable);
        }
    }
}

Player::~Player()
{
    delete mMovingTimer;
    delete mSpeedBonusTimer;
}

void Player::setUsername(const QString& username)
{
    mUsername = username;
}

QString Player::getUsername()
{
    return mUsername;
}

void Player::focusOutEvent(QFocusEvent*)
{
    if (!mIsEnemy && !mGameEngine->isFinished())
    {
        qDebug() << "setting focus on plr";
        setFocus();
    }
}

void Player::shootBullet()
{
    if (mHasBulletCooldown)
    {
        return;
    }

    if (!mIsEnemy)
    {
       mGameEngine->getParent()->getPacketWriter()->sendShootBullet();
    }

    QPointF position = pos();
    switch (mOrientation)
    {
        case Qt::Key_Up:
            position.ry() -= 30;
            break;

        case Qt::Key_Down:
            position.ry() += 65;
            break;

        case Qt::Key_Right:
            position.ry() += 18;
            position.rx() += 50;
            break;

        case Qt::Key_Left:
            position.ry() += 18;
            position.rx() -= 50;
            break;
    }

    bool isExtra = (mExtraDamageBuletsNumber > 0) ? true : false;
    if (isExtra && mExtraDamageBuletsNumber > 0)
    {
        --mExtraDamageBuletsNumber;
    }
    Bullet* bullet = new Bullet(mOrientation, position, mIsRed, isExtra, this);
    scene()->addItem(bullet);

    mHasBulletCooldown = true;
    QTimer::singleShot(BULLET_COOLDOWN, [=]
    {
       mHasBulletCooldown = false;
    });
}

bool Player::isEventAllowed(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        return false;
    }

    return QVector<Qt::Key>({Qt::Key_Up, Qt::Key_Down, Qt::Key_Right, Qt::Key_Left}).contains(static_cast<Qt::Key>(event->key()));
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space)
    {
        shootBullet();
        return;
    }

    if (!isEventAllowed(event))
    {
        return;
    }

    if (!mIsEnemy)
    {
       mGameEngine->getParent()->getPacketWriter()->sendKeyPressed(static_cast<Qt::Key>(event->key()));
    }

    mPressedKeys.push(mOrientation = static_cast<Qt::Key>(event->key()));
    if (!mMovingTimer->isActive())
    {
        mMovingTimer->start(GAME_UPDATE_TIME);
    }
}

void Player::keyReleaseEvent(QKeyEvent* event)
{
    if (!isEventAllowed(event))
    {
        return;
    }

    if (!mIsEnemy)
    {
       mGameEngine->getParent()->getPacketWriter()->sendKeyReleased(static_cast<Qt::Key>(event->key()), pos());
    }

    auto position = mPressedKeys.indexOf(static_cast<Qt::Key>(event->key()));
    if (position >= 0 && position < mPressedKeys.length())
    {
        mPressedKeys.remove(position);
    }

    if(mPressedKeys.isEmpty())
    {
        mMovingTimer->stop();
    }
    else
    {
        mOrientation = mPressedKeys.top();
    }
}

void Player::move()
{
    for (auto& item : this->collidingItems())
    {
        if (Bonus* bonus = dynamic_cast<Bonus*>(item))
        {
            gotBonus(bonus->getType());
            delete bonus;
            break;
        }
    }

    if (mPressedKeys.isEmpty())
    {
        return;
    }

    switch (mPressedKeys.top())
    {
        case Qt::Key_Left:
        {
            if (x() - mStep >= PLAYER_ME_START_X)
            {
                setX(x() - mStep);
            }
            setRotation(-90);
            break;
        }

        case Qt::Key_Right:
        {
            if (x() + mStep <= PLAYER_ENEMY_START_X)
            {
                setX(x() + mStep);
            }
            setRotation(90);
            break;
        }

        case Qt::Key_Up:
        {
            if (y() - mStep >= PLAYER_ME_START_Y)
            {
                setY(y() - mStep);
            }
            setRotation(0);
            break;
        }

        case Qt::Key_Down:
        {
            if (y() + mStep <= PLAYER_ENEMY_START_Y)
            {
                setY(y() + mStep);
            }
            setRotation(180);
            break;
        }
    }
}

void Player::gotShot(bool isExtra)
{
    mLives -= isExtra ? BULLET_BONUS_POWER : BULLET_POWER;
    mGameEngine->updateGui(mLives, !mIsRed);

    if (mLives <= 0)
    {
        gotKilled();
    }
}

void Player::gotBonus(quint32 type)
{
    switch (type)
    {
        case GAME_BONUS_TYPE_LIFE:
        {
            if (mLives == PLAYER_MAX_LIVES)
            {
                return;
            }

            ++mLives;
            mGameEngine->updateGui(mLives, !mIsRed);
            break;
        }
        case GAME_BONUS_TYPE_SPEED:
        {
            mStep = PLAYER_BONUS_STEP;
            if (mSpeedBonusTimer->isActive())
            {
               mSpeedBonusTimer->stop();
            }
            mSpeedBonusTimer->start(GAME_BONUS_SPEED_TIME);
        }
        case GAME_BONUS_TYPE_DAMAGE:
        {
            mExtraDamageBuletsNumber = GAME_BONUS_DAMAGE_NUMBER;
        }
    }
}

void Player::gotKilled()
{
    setPixmap(QPixmap(":/img/img/tombstone.png"));
    setRotation(0);
    mGameEngine->playerLost(this);

}
