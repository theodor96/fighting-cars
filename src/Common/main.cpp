#include <QApplication>

#include "UserInterface/MainWindow.h"
#include "Network/PacketWriter.h"

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    auto packetWriter = new PacketWriter();
    auto ui = new MainWindow(packetWriter);
    ui->show();



    //ui->startGame(true);



    return fightingCars.exec();
}
