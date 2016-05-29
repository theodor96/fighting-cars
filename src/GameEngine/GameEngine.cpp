#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"
#include "Network/PacketManager.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>

GameEngine::GameEngine(MainWindow* parent, bool mIsHost) :
    QObject(parent),
    mParent(parent),
    mScene(new QGraphicsScene(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, this)),
    mView(new QGraphicsView(mScene)),
    mPlayerMe(new Player(this, false, mIsHost)),
    mPlayerEnemy(new Player(this, true, mIsHost))
{
    parent->getPacketManager()->setParent(this);

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

MainWindow* GameEngine::getParent() const
{
    return mParent;
}

void GameEngine::gotKeyPressed(Qt::Key key)
{

    mPlayerEnemy->keyPressEvent(&QKeyEvent(QKeyEvent::KeyPress, key, Qt::NoModifier));
}

void GameEngine::gotKeyReleased(Qt::Key key)
{
    mPlayerEnemy->keyReleaseEvent(&QKeyEvent(QKeyEvent::KeyRelease, key, Qt::NoModifier));
}
