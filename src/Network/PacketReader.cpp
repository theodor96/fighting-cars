#include <QObject>
#include <QDebug>
#include <QUdpSocket>

#include "Network/PacketReader.h"
#include "Common/Constants.h"

PacketReader::PacketReader() :
    PacketManager(),
    mDatagram(),
    mDataStream(mDatagram)
{
    mSocket->bind(QHostAddress::Any, PEER_PORT);

    QObject::connect(mSocket, &QUdpSocket::readyRead, [=]
    {
        if (mSocket->hasPendingDatagrams())
        {
            mDatagram.resize(mSocket->pendingDatagramSize());
            mSocket->readDatagram(mDatagram.data(), mDatagram.size(), &mPeerAddress);
            receivedDatagram();
        }
    });
}

PacketReader::~PacketReader()
{

}

void PacketReader::receivedDatagram()
{
    qDebug() << "read a datagram";
}
