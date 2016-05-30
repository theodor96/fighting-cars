#include <QDebug>
#include <QIODevice>
#include <QUdpSocket>

#include "Network/PacketWriter.h"
#include "Common/Constants.h"

PacketWriter::PacketWriter() :
    PacketManager(),
    mDatagram(),
    mDataStream(&mDatagram, QIODevice::WriteOnly)
{

}

PacketWriter::~PacketWriter()
{

}

void PacketWriter::sendConnect(const QString& username)
{
    mDataStream << MESSAGE_TYPE_CONNECTION;
    mDataStream << MESSAGE_TYPE_CONNECTION_INITIATE;
    mDataStream << username;
    sendPacket();
}

void PacketWriter::sendReceived()
{
    mDataStream << MESSAGE_TYPE_CONNECTION;
    mDataStream << MESSAGE_TYPE_CONNECTION_RECEIVED;
    sendPacket();
}

void PacketWriter::sendAccept(const QString& username)
{
    qDebug() << "before writing, size =" << mDatagram.size();

    mDataStream << MESSAGE_TYPE_CONNECTION;
    mDataStream << MESSAGE_TYPE_CONNECTION_ACCEPT;
    mDataStream << username;

    qDebug() << "after writing, siuze = " << mDatagram.size();

    sendPacket();
}

void PacketWriter::sendReject()
{
    mDataStream << MESSAGE_TYPE_CONNECTION;
    mDataStream << MESSAGE_TYPE_CONNECTION_REJECT;
    sendPacket();
}

void PacketWriter::sendAck()
{
    mDataStream << MESSAGE_TYPE_CONNECTION;
    mDataStream << MESSAGE_TYPE_CONNECTION_ACK;
    sendPacket();
}

void PacketWriter::sendKeyPressed(Qt::Key key)
{
    mDataStream << MESSAGE_TYPE_KEY_PRESS;
    mDataStream << static_cast<qint64>(key);
    sendPacket();
}

void PacketWriter::sendKeyReleased(Qt::Key key, const QPointF& myPosition)
{
    mDataStream << MESSAGE_TYPE_KEY_RELEASE;
    mDataStream << static_cast<qint64>(key);
    mDataStream << myPosition.x();
    mDataStream << myPosition.y();
    sendPacket();
}

void PacketWriter::sendShootBullet()
{
    mDataStream << MESSAGE_TYPE_KEY_SHOOT;
    sendPacket();
}

void PacketWriter::sendSpawnBonus(quint32 type, const QPointF& position)
{
    mDataStream << MESSAGE_TYPE_BONUS_SPAWN;
    mDataStream << type;
    mDataStream << position.x();
    mDataStream << position.y();
    sendPacket();
}

void PacketWriter::sendPacket()
{
    mSocket->writeDatagram(mDatagram, mPeerAddress, PEER_PORT);

    mDatagram.clear();

    qDebug() << "wrote a packet to " << mPeerAddress;
}
