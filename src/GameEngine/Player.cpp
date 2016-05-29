#include "GameEngine/GameEngine.h"
#include "GameEngine/Player.h"
#include "Common/Constants.h"
#include "UserInterface/MainWindow.h"
#include "Network/PacketManager.h"

#include <QKeyEvent>
#include <QDebug>
#include <QVector>
#include <QTimer>

Player::Player(GameEngine* parent, bool isEnemy, bool isHost) :
    QGraphicsPixmapItem(),
    mGameEngine(parent),
    mUsername(),
    mIsEnemy(isEnemy == isHost),
    mMovingTimer(new QTimer()),
    mStep(PLAYER_DEFAULT_STEP),
    mPressedKeys()
{
    setTransformOriginPoint(15, 30);
    QObject::connect(mMovingTimer, &QTimer::timeout, [=]
    {
        move();
    });

    if (isEnemy)
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
        qDebug() << "shooot";
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
    else
    {
        qDebug() << "as trimite pachete da is enemy si nu pot";
    }

    mPressedKeys.push(static_cast<Qt::Key>(event->key()));
    if (!mMovingTimer->isActive())
    {
        mMovingTimer->start(PLAYER_MOVE_UPDATE_TIME);
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
       mGameEngine->getParent()->getPacketManager()->sendKeyReleased(static_cast<Qt::Key>(event->key()));
    }

    mPressedKeys.remove(mPressedKeys.indexOf(static_cast<Qt::Key>(event->key())));
    if(mPressedKeys.isEmpty())
    {
        mMovingTimer->stop();
    }
}

void Player::move()
{
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
