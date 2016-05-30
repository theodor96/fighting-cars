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

QHostAddress& PacketManager::getPeerAddress()
{
    return mPeerAddress;
}
