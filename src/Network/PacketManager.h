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
    bool hasParent() const;
    QHostAddress& getPeerAddress();

protected:
    QUdpSocket* mSocket;
    QHostAddress mPeerAddress;

    template<typename ParentPtr>
    ParentPtr getParent() const
    {
        return static_cast<ParentPtr>(mParent);
    }

private:
    QObject* mParent;
};

#endif // PACKETMANAGER_H

