#include "GameEngine/Bonus.h"
#include "Common/Constants.h"

#include <QGraphicsScene>

Bonus::Bonus(quint32 type, const QPointF& position) :
    QGraphicsPixmapItem(),
    mType(type)
{
    setPixmap(QPixmap(QString(":/img/img/bonus_%1.png").arg(type)));
    setPos(position);
}

Bonus::~Bonus()
{
    scene()->removeItem(this);
}

quint32 Bonus::getType() const
{
    return mType;
}
