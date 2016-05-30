#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

#include "GameEngine/Bullet.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"

Bullet::Bullet(Qt::Key direction, const QPointF& position, bool isEnemyBullet) :
    QGraphicsPixmapItem(),
    mDirection(direction),
    mTimer(new QTimer())
{
    setPixmap(QPixmap(QString(":/img/img/bullet%1.png").arg(isEnemyBullet ? "_enemy" : "")));
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
            plr->gotShot();
            delete this;
            return;
        }
    }

    if (y() < PLAYER_ME_START_Y || y() > PLAYER_ENEMY_START_Y || x() < PLAYER_ME_START_X || x() > PLAYER_ENEMY_START_X)
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
