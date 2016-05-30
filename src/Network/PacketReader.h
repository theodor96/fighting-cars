#ifndef PACKETREADER_H
#define PACKETREADER_H

#include <QByteArray>
#include <QDataStream>

#include "Network/PacketManager.h"

class PacketReader :
        public PacketManager
{
public:
    PacketReader();
    virtual ~PacketReader();

private:
    QByteArray mDatagram;
    QDataStream mDataStream;

    void receivedDatagram();
};

#endif // PACKETREADER_H
