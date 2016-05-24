#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QObject>

class QUdpSocket;
class WaitPopup;

class PacketManager :
        public QObject
{
    Q_OBJECT

public:
    PacketManager();
    ~PacketManager();

    void receivedDatagram();
    void setParent(QObject*);

    void setIPAddress(const QString&);

    void sendConnectRequest(const QString&);

    void sendCancelRequest();

private:
    QString mIPAddress;
    QObject* mParent;
    QUdpSocket* mSocket;
};

#endif // PACKETMANAGER_H

