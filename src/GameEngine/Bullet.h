#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class QTimer;
class Player;

class Bullet :
        public QGraphicsPixmapItem

{
public:
    Bullet(Qt::Key, const QPointF&, bool, bool, Player*);
    ~Bullet();

private:
    Qt::Key mDirection;
    QTimer* mTimer;
    bool mIsExtra;
    Player* mOwner;

    void move();
};

#endif // BULLET_H
