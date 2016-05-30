#ifndef PACKETREADER_H
#define PACKETREADER_H

#include <QByteArray>
#include <QDataStream>

#include "Network/PacketManager.h"

class PacketWriter;

class PacketReader :
        public PacketManager
{
public:
    explicit PacketReader(PacketWriter*);
    virtual ~PacketReader();

    void listen();
    void doNotListen();

private:
    PacketWriter* mPacketWriter;
    QByteArray mDatagram;
    QDataStream mDataStream;

    void receivedDatagram();
};

#endif // PACKETREADER_H
