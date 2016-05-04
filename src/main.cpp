#include <QApplication>

#include "UserInterface.h"

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    //UI ownership will be transferred to the game engine once it starts running
    auto ui = new UserInterface();
    ui->show();

    return fightingCars.exec();
}
