#include <QUdpSocket>

#include "PacketManager.h"
#include "UserInterface/WaitPopup.h"
#include "UserInterface/ConnectPopup.h"
#include "Common/Constants.h"
#include "GameEngine/GameEngine.h"

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

void PacketManager::sendReceived()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_CONNECTION;
    out << MESSAGE_TYPE_CONNECTION_RECEIVED;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
    qDebug() << "sent received ";
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

void PacketManager::sendKeyPressed(Qt::Key key)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_KEY_PRESS;
    out << static_cast<qint64>(key);

    qDebug() << "sending " << MESSAGE_TYPE_KEY_PRESS << " " << static_cast<qint64>(key) << " to " << mIPAddress;
    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);

}

void PacketManager::sendKeyReleased(Qt::Key key, const QPointF& myPosition)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_KEY_RELEASE;
    out << static_cast<qint64>(key);
    out << myPosition.x();
    out << myPosition.y();

    qDebug() << "sending " << MESSAGE_TYPE_KEY_RELEASE << " " << static_cast<qint64>(key) << " to " << mIPAddress;
    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
}

void PacketManager::sendShootBullet()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_KEY_SHOOT;

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
}

void PacketManager::sendSpawnBonus(quint32 type, const QPointF& position)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << MESSAGE_TYPE_BONUS_SPAWN;
    out << type;
    out << position.x();
    out << position.y();

    mSocket->writeDatagram(datagram, QHostAddress(mIPAddress), PEER_PORT);
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

                case MESSAGE_TYPE_CONNECTION_RECEIVED:
                {
                    auto connectPopup = static_cast<ConnectPopup*>(mParent);
                    connectPopup->gotReceived();

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

                    break;
                }

                case MESSAGE_TYPE_CONNECTION_ACK:
                {
                    auto waitPopup = static_cast<WaitPopup*>(mParent);
                    waitPopup->gotAckConfirmation();

                    break;
                }
            }

            break;
        }

        case MESSAGE_TYPE_KEY_PRESS:
        {
            qDebug() << "got key press";
            qint64 key;
            in >> key;

            auto gameEngine = static_cast<GameEngine*>(mParent);
            gameEngine->gotKeyPressed(static_cast<Qt::Key>(key));

            break;
        }

        case MESSAGE_TYPE_KEY_RELEASE:
        {
            qDebug() << "got key release";
            qint64 key;
            qreal peerX;
            qreal peerY;

            in >> key;
            in >> peerX;
            in >> peerY;

            auto gameEngine = static_cast<GameEngine*>(mParent);
            gameEngine->gotKeyReleased(static_cast<Qt::Key>(key), QPointF(peerX, peerY));

            break;
        }

        case MESSAGE_TYPE_KEY_SHOOT:
        {
            qDebug() << "got key shoot";

            auto gameEngine = static_cast<GameEngine*>(mParent);
            gameEngine->gotShootBullet();

            break;
        }

        case MESSAGE_TYPE_BONUS_SPAWN:
        {
            qDebug() << "got bonus received";
            quint32 type;
            qreal bonusX;
            qreal bonusY;

            in >> type;
            in >> bonusX;
            in >> bonusY;

            auto gameEngine = static_cast<GameEngine*>(mParent);
            gameEngine->spawnBonus(type, QPointF(bonusX, bonusY));

            break;
        }
    }
}
