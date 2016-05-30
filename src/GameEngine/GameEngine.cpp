#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"
#include "Network/PacketManager.h"
#include "GameEngine/Bonus.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>

GameEngine::GameEngine(MainWindow* parent, bool isHost) :
    QObject(parent),
    mParent(parent),
    mScene(new QGraphicsScene(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, this)),
    mView(new QGraphicsView(mScene)),
    mPlayerMe(new Player(this, false, isHost)),
    mPlayerEnemy(new Player(this, true, isHost)),
    mIsHost(isHost),
    mBonusTimer(new QTimer())
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

    if (isHost)
    {
        qsrand(QTime::currentTime().msec());
        this->connect(mBonusTimer, &QTimer::timeout, this, [=]
        {
            spawnBonus(getRandomBetween(GAME_BONUS_TYPE_FIRST, GAME_BONUS_TYPE_LAST),
                       QPointF(getRandomBetween(PLAYER_ME_START_X, PLAYER_ENEMY_START_X), getRandomBetween(PLAYER_ME_START_Y, PLAYER_ENEMY_START_Y)));

            mBonusTimer->stop();
            mBonusTimer->start(getRandomBetween(GAME_BONUS_SPAWN_MIN, GAME_BONUS_SPAWN_MAX));
        });

        mBonusTimer->start(getRandomBetween(GAME_BONUS_SPAWN_MIN, GAME_BONUS_SPAWN_MAX));
    }
}

GameEngine::~GameEngine()
{
    delete mView;
    delete mPlayerMe;
    delete mPlayerEnemy;
    delete mBonusTimer;
}

MainWindow* GameEngine::getParent() const
{
    return mParent;
}

void GameEngine::gotKeyPressed(Qt::Key key)
{
    auto player = mIsHost ? mPlayerEnemy : mPlayerMe;
    auto event = QKeyEvent(QKeyEvent::KeyPress, key, Qt::NoModifier);
    player->keyPressEvent(&event);
}

void GameEngine::gotKeyReleased(Qt::Key key, const QPointF& peerPosition)
{
    auto player = mIsHost ? mPlayerEnemy : mPlayerMe;
    auto event = QKeyEvent(QKeyEvent::KeyRelease, key, Qt::NoModifier);
    player->keyReleaseEvent(&event);
    player->setPos(peerPosition);
}

void GameEngine::gotShootBullet()
{
    auto player = mIsHost ? mPlayerEnemy : mPlayerMe;
    player->shootBullet();
}

void GameEngine::spawnBonus(quint32 type, const QPointF& position)
{
    mScene->addItem(new Bonus(type, position));

    if (mIsHost)
    {
        mParent->getPacketManager()->sendSpawnBonus(type, position);
    }
}

quint32 GameEngine::getRandomBetween(quint32 min, quint32 max) const
{
    return qrand() % ((max + 1) - min) + min;
}
