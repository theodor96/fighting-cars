#include <QApplication>

#include "UserInterface/MainWindow.h"




#include "ui_MainWindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QDebug>
#include <QMovie>

int main(int argc, char** argv)
{
    QApplication fightingCars(argc, argv);

    //UI ownership will be transferred to the game engine once it starts running
    //auto ui = new UserInterface();
    //ui->show();




    const QImage background(":/img/img/game_background.png");

    QGraphicsScene* scene = new QGraphicsScene(0, 0, background.width(), background.height());

    QGraphicsView* view = new QGraphicsView(scene);

    scene->setBackgroundBrush(QBrush(background));
    view->setFixedSize(background.size());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




     auto ui = new MainWindow();
    ui->show();



    //ui->setCentralWidget(view);

    return fightingCars.exec();
}
