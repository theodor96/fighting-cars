#include <QApplication>

#include "userinterface.h"

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    UserInterface ui;
    ui.show();

    return fightingCars.exec();
}
