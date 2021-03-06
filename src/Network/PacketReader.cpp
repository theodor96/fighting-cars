#include <QObject>
#include <QDebug>
#include <QUdpSocket>

#include "Network/PacketReader.h"
#include "Network/PacketWriter.h"
#include "Common/Constants.h"
#include "UserInterface/WaitPopup.h"
#include "UserInterface/ConnectPopup.h"
#include "GameEngine/GameEngine.h"

PacketReader::PacketReader(PacketWriter* packetWriter) :
    PacketManager(),
    mPacketWriter(packetWriter),
    mDatagram(),
    mDataStream(&mDatagram, QIODevice::ReadOnly)
{
    QObject::connect(mSocket, &QUdpSocket::readyRead, [=]
    {
        if (!hasParent())
        {
            return;
        }

        if (mSocket->hasPendingDatagrams())
        {
            mDatagram.resize(mSocket->pendingDatagramSize());
            mSocket->readDatagram(mDatagram.data(), mDatagram.size(), &mPacketWriter->getPeerAddress());
            receivedDatagram();
        }
    });
}

PacketReader::~PacketReader()
{
    mSocket->close();
}

void PacketReader::listen()
{
    mSocket->bind(QHostAddress::Any, PEER_PORT);
}

void PacketReader::doNotListen()
{
    mSocket->disconnectFromHost();
}

void PacketReader::receivedDatagram()
{
    quint8 messageType;
    mDataStream >> messageType;

    switch (messageType)
    {
        case MESSAGE_TYPE_CONNECTION:
        {
            quint8 connectionType;
            mDataStream >> connectionType;

            qDebug() << "conntype = " << connectionType;

            switch (connectionType)
            {
                case MESSAGE_TYPE_CONNECTION_INITIATE:
                {
                    QString enemyUsername;
                    mDataStream >> enemyUsername;

                    getParent<WaitPopup*>()->gotConnectRequest(enemyUsername);
                    break;
                }

                case MESSAGE_TYPE_CONNECTION_RECEIVED:
                {
                    getParent<ConnectPopup*>()->gotReceived();
                    break;
                }

                case MESSAGE_TYPE_CONNECTION_ACCEPT:
                {
                    QString enemyUsername;
                    mDataStream >> enemyUsername;

                    qDebug() << "got accept";

                    getParent<ConnectPopup*>()->gotAccept(enemyUsername);
                    break;
                }

                case MESSAGE_TYPE_CONNECTION_REJECT:
                {
                    getParent<ConnectPopup*>()->gotReject();
                    break;
                }

                case MESSAGE_TYPE_CONNECTION_ACK:
                {
                    getParent<WaitPopup*>()->gotAckConfirmation();
                    break;
                }
            }

            break;
        }

        case MESSAGE_TYPE_KEY_PRESS:
        {
            qint64 key;
            mDataStream >> key;

            getParent<GameEngine*>()->gotKeyPressed(static_cast<Qt::Key>(key));
            break;
        }

        case MESSAGE_TYPE_KEY_RELEASE:
        {
            qint64 key;
            qreal peerX;
            qreal peerY;
            mDataStream >> key >> peerX >> peerY;

            getParent<GameEngine*>()->gotKeyReleased(static_cast<Qt::Key>(key), QPointF(peerX, peerY));
            break;
        }

        case MESSAGE_TYPE_KEY_SHOOT:
        {
            getParent<GameEngine*>()->gotShootBullet();
            break;
        }

        case MESSAGE_TYPE_BONUS_SPAWN:
        {
            quint32 type;
            qreal bonusX;
            qreal bonusY;
            mDataStream >> type >> bonusX >> bonusY;

            getParent<GameEngine*>()->spawnBonus(type, QPointF(bonusX, bonusY));
            break;
        }
    }
}
