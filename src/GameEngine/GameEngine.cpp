#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

GameEngine::GameEngine(MainWindow* parent) :
    QObject(parent),
    mParent(parent),
    mScene(new QGraphicsScene(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, this)),
    mView(new QGraphicsView(mScene)),
    mPlayerMe(new Player(this, false)),
    mPlayerEnemy(new Player(this, true))
{
    const QImage background(":/img/img/game_background.png");
    mScene->setBackgroundBrush(QBrush(background));

    mView->setFixedSize(background.size());
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parent->setCentralWidget(mView);

    mPlayerMe->setUsername(mParent->getUsername());
    mPlayerEnemy->setUsername(mParent->getEnemyUsername());

    mScene->addItem(mPlayerMe);
    mScene->addItem(mPlayerEnemy);
}

GameEngine::~GameEngine()
{

}
