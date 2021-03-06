#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

#include "GameEngine/Bullet.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"

Bullet::Bullet(Qt::Key direction, const QPointF& position, bool isEnemyBullet, bool isExtra, Player* owner) :
    QGraphicsPixmapItem(),
    mDirection(direction),
    mTimer(new QTimer()),
    mIsExtra(isExtra),
    mOwner(owner)
{
    setPixmap(QPixmap(QString(":/img/img/bullet%1.png").arg(isExtra? "_extra" : (isEnemyBullet ? "_enemy" : ""))));
    setPos(position);

    QObject::connect(mTimer, &QTimer::timeout, [=]
    {
        move();
    });

    mTimer->start(GAME_UPDATE_TIME);
}

Bullet::~Bullet()
{
    scene()->removeItem(this);
    mTimer->stop();
    delete mTimer;
    qDebug() << "a bullet got deleted";
}

void Bullet::move()
{
    for (auto& item : this->collidingItems())
    {
        if (Player* plr = dynamic_cast<Player*>(item))
        {
            if (plr == mOwner)
            {
                continue;
            }

            plr->gotShot(mIsExtra);
            delete this;
            return;
        }
    }

    if (y() < PLAYER_ME_START_Y - GAME_BOARD_PADDING ||
        y() > PLAYER_ENEMY_START_Y + GAME_BOARD_PADDING||
        x() < PLAYER_ME_START_X - GAME_BOARD_PADDING ||
        x() > PLAYER_ENEMY_START_X + GAME_BOARD_PADDING)
    {
        delete this;
        return;
    }

    switch (mDirection)
    {
        case Qt::Key_Up:
        {
            setY(y() - BULLET_STEP);

            break;
        }

        case Qt::Key_Down:
        {
            setY(y() + BULLET_STEP);
            break;
        }

        case Qt::Key_Left:
        {
            setX(x() - BULLET_STEP);
            break;
        }

        case Qt::Key_Right:
        {
            setX(x() + BULLET_STEP);
            break;
        }
    }
}
