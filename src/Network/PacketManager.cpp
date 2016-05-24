#include <QUdpSocket>

#include "PacketManager.h"
#include "UserInterface/WaitPopup.h"
#include "UserInterface/ConnectPopup.h"
#include "Common/Constants.h"

PacketManager::PacketManager() :
    QObject(),
    mIPAddress(),
    mParent(nullptr),
    mSocket(new QUdpSocket(this))
{
    mSocket->bind(QHostAddress::Any, PEER_PORT);
    connect(mSocket, &QUdpSocket::readyRead, this, [=]
    {
        receivedDatagram();
    });
}

PacketManager::~PacketManager()
{

}

void PacketManager::setParent(QObject* parent)
{
    mParent = parent;
}

void PacketManager::setIPAddress(const QString& IPAddress)
{
    mIPAddress = IPAddress;
}

void PacketManager::sendConnectRequest(const QString& username)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_CONNECTION;
    out << MESSAGE_TYPE_CONNECTION_INITIATE;
    out << username;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
    qDebug() << "sent datagram 1 1 " << username << " to ip " << mIPAddress << "on port " << PEER_PORT;
}

void PacketManager::sendAccept(const QString& username)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_CONNECTION;
    out << MESSAGE_TYPE_CONNECTION_ACCEPT;
    out << username;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
    qDebug() << "sent accept to " << mIPAddress;
}

void PacketManager::sendReject()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_CONNECTION;
    out << MESSAGE_TYPE_CONNECTION_REJECT;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
    qDebug() << "sent reject to " << mIPAddress;
}

void PacketManager::sendAck()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_CONNECTION;
    out << MESSAGE_TYPE_CONNECTION_ACK;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
    qDebug() << "sent ack";
}

void PacketManager::receivedDatagram()
{
    QHostAddress peerIPAddress;
    QByteArray datagram;
    while (mSocket->hasPendingDatagrams())
    {
        datagram.resize(mSocket->pendingDatagramSize());
        mSocket->readDatagram(datagram.data(), datagram.size(), &peerIPAddress);
    }

    if (mParent == nullptr)
    {
        return;
    }

    QDataStream in(&datagram, QIODevice::ReadOnly);
    quint8 messageType;

    in >> messageType;
    switch (messageType)
    {
        case MESSAGE_TYPE_CONNECTION:
        {
            quint8 connectionType;
            in >> connectionType;

            switch (connectionType)
            {
                case MESSAGE_TYPE_CONNECTION_INITIATE:
                {
                    QString enemyUsername;
                    in >> enemyUsername;

                    mIPAddress = peerIPAddress.toString();

                    auto waitPopup = static_cast<WaitPopup*>(mParent);
                    waitPopup->gotConnectRequest(enemyUsername);

                    break;
                }

                case MESSAGE_TYPE_CONNECTION_ACCEPT:
                {
                    QString enemyUsername;
                    in >> enemyUsername;

                    auto connectPopup = static_cast<ConnectPopup*>(mParent);
                    connectPopup->gotAccept(enemyUsername);

                    break;
                }

                case MESSAGE_TYPE_CONNECTION_REJECT:
                {
                    qDebug() << "got message tpye reject";
                    auto connectPopup = static_cast<ConnectPopup*>(mParent);
                    qDebug () << mParent << connectPopup;
                    connectPopup->gotReject();
                }

                case MESSAGE_TYPE_CONNECTION_ACK:
                {
                    auto waitPopup = static_cast<WaitPopup*>(mParent);
                    waitPopup->gotAckConfirmation();
                }
            }
        }
    }

    /*qint64 keyInt;
    Qt::Key key;

    in >> type;
    in >> keyInt;
    key = static_cast<Qt::Key>(keyInt);

    if (type == 1)
    {
        mPlr->keyPressEvent(&KeyEvent(key));
    }
    else
    {
        if (type == 2)
        {
            mPlr->keyReleaseEvent(&KeyEvent(key));
        }
    }

    qDebug() << "Receiving*/
}
