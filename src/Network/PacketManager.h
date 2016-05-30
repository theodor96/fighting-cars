#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QString>
#include <QHostAddress>

class QUdpSocket;
class QObject;

class PacketManager
{

public:
    PacketManager();
    virtual ~PacketManager();

    void setParent(QObject*);

    const QHostAddress& getPeerAddress() const;
    void setPeerAddress(const QHostAddress&);

protected:
    QUdpSocket* mSocket;
    QHostAddress mPeerAddress;

    template<typename Parent>
    Parent* getParent() const
    {
        return static_cast<Parent*>(mParent);
    }

private:
    QObject* mParent;
};

#endif // PACKETMANAGER_H

