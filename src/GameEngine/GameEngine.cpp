#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"
#include "Network/PacketManager.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>

GameEngine::GameEngine(MainWindow* parent, bool isHost) :
    QObject(parent),
    mParent(parent),
    mScene(new QGraphicsScene(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, this)),
    mView(new QGraphicsView(mScene)),
    mPlayerMe(new Player(this, false, isHost)),
    mPlayerEnemy(new Player(this, true, isHost)),
    mIsHost(isHost)
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

    add(mPlayerMe);
    add(mPlayerEnemy);
}

GameEngine::~GameEngine()
{

}

void GameEngine::add(QGraphicsItem* item)
{
    mScene->addItem(item);
}

MainWindow* GameEngine::getParent() const
{
    return mParent;
}

void GameEngine::gotKeyPressed(Qt::Key key)
{
    auto player = mIsHost ? mPlayerEnemy : mPlayerMe;
    player->keyPressEvent(&QKeyEvent(QKeyEvent::KeyPress, key, Qt::NoModifier));
}

void GameEngine::gotKeyReleased(Qt::Key key, const QPointF& peerPosition)
{
    auto player = mIsHost ? mPlayerEnemy : mPlayerMe;
    player->keyReleaseEvent(&QKeyEvent(QKeyEvent::KeyRelease, key, Qt::NoModifier));
    player->setPos(peerPosition);
}
