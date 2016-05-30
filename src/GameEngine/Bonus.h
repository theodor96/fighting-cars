#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsPixmapItem>

class QPointF;

class Bonus :
        public QGraphicsPixmapItem
{
public:
    Bonus(quint32, const QPointF&);
    ~Bonus();

    quint32 getType() const;

private:
    quint32 mType;
};

#endif // BONUS_H
