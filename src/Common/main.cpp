#include <QApplication>

#include "UserInterface/MainWindow.h"
#include "Network/PacketWriter.h"
#include "Network/PacketReader.h"

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    auto packetWriter = new PacketWriter();
    auto packetReader = new PacketReader(packetWriter);

    auto ui = new MainWindow(packetWriter, packetReader);
    ui->show();

    ui->startGame(true);



    return fightingCars.exec();
}
