#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class QGraphicsItem;
class QTimer;
class Vehicle;

class Bullet :
        public QGraphicsPixmapItem

{
public:
    Bullet(Qt::Key, const QPointF&, bool, bool);
    ~Bullet();

private:
    Qt::Key mDirection;
    QTimer* mTimer;
    bool mIsExtra;

    void move();
};

#endif // BULLET_H
