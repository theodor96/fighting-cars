#include <QApplication>

#include "UserInterface/MainWindow.h"
#include "Network/PacketManager.h"

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    auto packetManager = new PacketManager();
    auto ui = new MainWindow(packetManager);
    ui->show();



    ui->startGame();



    return fightingCars.exec();
}
