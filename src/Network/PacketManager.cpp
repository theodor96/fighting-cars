#include <QUdpSocket>
#include <QObject>

#include "Network/PacketManager.h"

PacketManager::PacketManager() :
    mSocket(new QUdpSocket()),
    mPeerAddress()
{

}

PacketManager::~PacketManager()
{
    delete mSocket;
}

void PacketManager::setParent(QObject* parent)
{
    mParent = parent;
}

const QHostAddress& PacketManager::getPeerAddress() const
{
    return mPeerAddress;
}

void PacketManager::setPeerAddress(const QHostAddress& peerAddress)
{
    mPeerAddress = peerAddress;
}
