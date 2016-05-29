#include "GameEngine/GameEngine.h"
#include "GameEngine/Player.h"
#include "Common/Constants.h"
#include "UserInterface/MainWindow.h"
#include "Network/PacketManager.h"
#include "GameEngine/Bullet.h"

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
    mStep(PLAYER_DEFAULT_STEP),
    mPressedKeys(),
    mOrientation(isRed ? Qt::Key_Left : Qt::Key_Right)
{
    setTransformOriginPoint(15, 30);
    QObject::connect(mMovingTimer, &QTimer::timeout, [=]
    {
        move();
    });

    if (isRed)
    {
        setPixmap(QPixmap(":/img/img/car_enemy.png"));
        setPos(PLAYER_ENEMY_START_X, PLAYER_ENEMY_START_Y);
        qDebug() << "enemy plr constructed";
        setRotation(-90);

        if (!isHost)
        {
            setFlag(QGraphicsItem::ItemIsFocusable);
            setFocus();
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
            setFocus();
        }
    }
}

Player::~Player()
{

}

void Player::setUsername(const QString& username)
{
    mUsername = username;
}

void Player::focusOutEvent(QFocusEvent*)
{
    if (!mIsEnemy)
    {
        setFocus();
    }
}

void Player::shootBullet()
{
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

    Bullet* bullet = new Bullet(mOrientation, position, mIsRed);
    scene()->addItem(bullet);
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
       mGameEngine->getParent()->getPacketManager()->sendKeyPressed(static_cast<Qt::Key>(event->key()));
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
       mGameEngine->getParent()->getPacketManager()->sendKeyReleased(static_cast<Qt::Key>(event->key()), pos());
    }

    mPressedKeys.remove(mPressedKeys.indexOf(static_cast<Qt::Key>(event->key())));
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
        //bonus collection
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

void Player::gotShot()
{
    qDebug() << "I am " << mIsEnemy << " and i got shot";
}
