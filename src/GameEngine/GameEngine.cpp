#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

GameEngine::GameEngine(MainWindow* parent) :
    QObject(parent),
    mParent(parent)
{
    qDebug() << "game engine ctor";

    const QImage background(":/img/img/game_background.png");

    QGraphicsScene* scene = new QGraphicsScene(0, 0, background.width(), background.height());

    QGraphicsView* view = new QGraphicsView(scene);

    scene->setBackgroundBrush(QBrush(background));
    view->setFixedSize(background.size());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parent->setCentralWidget(view);
}

GameEngine::~GameEngine()
{

}
