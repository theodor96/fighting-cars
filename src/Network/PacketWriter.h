#ifndef PACKETWRITER_H
#define PACKETWRITER_H

#include <QByteArray>
#include <QDataStream>

#include "Network/PacketManager.h"

class PacketWriter :
        public PacketManager
{
public:
    PacketWriter();
    virtual ~PacketWriter();

    void sendConnect(const QString&);
    void sendReceived();
    void sendAccept(const QString&);
    void sendReject();
    void sendAck();
    void sendKeyPressed(Qt::Key);
    void sendKeyReleased(Qt::Key, const QPointF&);
    void sendShootBullet();
    void sendSpawnBonus(quint32, const QPointF&);

private:
    QByteArray mDatagram;
    QDataStream mDataStream;

    void sendPacket();
};

#endif // PACKETWRITER_H
