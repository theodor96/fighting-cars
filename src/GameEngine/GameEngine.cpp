#include "GameEngine/GameEngine.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "GameEngine/Player.h"
#include "Network/PacketWriter.h"
#include "Network/PacketReader.h"
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
    mScene(new QGraphicsScene(0, 0, MAIN_WINDOW_WIDTH - 2, MAIN_WINDOW_HEIGHT - 2, this)),
    mView(new QGraphicsView(mScene)),
    mPlayerMe(new Player(this, false, isHost)),
    mPlayerEnemy(new Player(this, true, isHost)),
    mIsHost(isHost),
    mBonusTimer(new QTimer()),
    mCountdownText(nullptr),
    vLivesBlue(),
    vLivesRed()
{
    parent->reparentPacketReader(this);
    parent->getPacketReader()->listen();

    const QImage background(":/img/img/game_background.png");
    mScene->setBackgroundBrush(QBrush(background));

    mView->setFixedSize(background.size());
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parent->setCentralWidget(mView);

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

        mPlayerMe->setUsername(mParent->getUsername());
        mPlayerEnemy->setUsername(mParent->getEnemyUsername());
        qDebug() << "names are set";
    }
    else
    {
        mPlayerEnemy->setUsername(mParent->getUsername());
        mPlayerMe->setUsername(mParent->getEnemyUsername());
        qDebug() << "names are set";
    }

    mScene->addItem(mPlayerMe);
    mScene->addItem(mPlayerEnemy);
    buildGui();

    countdown();
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

void GameEngine::playerLost(Player* loser)
{
    mBonusTimer->stop();

    QGraphicsSimpleTextItem* finalText;
    if ((loser == mPlayerMe) == mIsHost)
    {
        finalText = mScene->addSimpleText("You Lost!");
    }
    else
    {
        finalText = mScene->addSimpleText("You Won!");
    }
    finalText->setScale(7);
    finalText->setPos(MAIN_WINDOW_WIDTH / 2 - 166, MAIN_WINDOW_HEIGHT / 2 - 75);

    QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap(":/img/img/tombstone.png"));
    tombstone->setPos(loser->pos());
    mScene->addItem(tombstone);

    delete mPlayerMe;
    mPlayerMe = nullptr;
    delete mPlayerEnemy;
    mPlayerEnemy = nullptr;
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
        mParent->getPacketWriter()->sendSpawnBonus(type, position);
    }
}

quint32 GameEngine::getRandomBetween(quint32 min, quint32 max) const
{
    return qrand() % ((max + 1) - min) + min;
}

void GameEngine::buildGui()
{
    mCountdownText = mScene->addSimpleText(QString::number(GAME_COUNTDOWN_TIME));
    mCountdownText->setPos(MAIN_WINDOW_WIDTH / 2 - 50, MAIN_WINDOW_HEIGHT / 2 - 150);
    mCountdownText->setScale(20);

    QGraphicsSimpleTextItem* textNameBlue = mScene->addSimpleText(mPlayerMe->getUsername());
    textNameBlue->setPos(4, -2);
    textNameBlue->setScale(2);

    for (quint8 i = 0; i < PLAYER_MAX_LIVES; i++)
    {
        vLivesBlue.push_back(mScene->addPixmap(QPixmap(":/img/img/bonus_1.png")));
        vLivesBlue[i]->setPos(30 * i + 4, 25);
        if (i >= PLAYER_DEFAULT_LIVES)
        {
            vLivesBlue[i]->setVisible(false);
        }
    }

    QGraphicsSimpleTextItem* textNameRed = mScene->addSimpleText(mPlayerEnemy->getUsername());
    textNameRed->setPos(4, MAIN_WINDOW_HEIGHT - 53);
    textNameRed->setScale(2);

    for (quint8 i = 0; i < PLAYER_MAX_LIVES; i++)
    {
        vLivesRed.push_back(mScene->addPixmap(QPixmap(":/img/img/bonus_1.png")));
        vLivesRed[i]->setPos((30 * i) + 4, MAIN_WINDOW_HEIGHT - 27);
        if (i >= PLAYER_DEFAULT_LIVES)
        {
            vLivesRed[i]->setVisible(false);
        }
    }
}

void GameEngine::updateGui(int nLives, bool isBlue)
{
    for (quint8 i = 0; i < PLAYER_MAX_LIVES; i++)
    {
        if(isBlue)
        {
            if (i >= nLives)
            {
                vLivesBlue[i]->setVisible(false);
            }
            else
            {
                vLivesBlue[i]->setVisible(true);
            }
        }
        else
        {
            if (i >= nLives)
            {
                vLivesRed[i]->setVisible(false);
            }
            else
            {
                vLivesRed[i]->setVisible(true);
            }
        }
    }
}

void GameEngine::countdown()
{
    static quint8 countdown = GAME_COUNTDOWN_TIME;
    auto countdownTimer = new QTimer();
    countdownTimer->start(1000);

    QObject::connect(countdownTimer, &QTimer::timeout, [=]
    {
        if (--countdown == 0)
        {
            countdownTimer->stop();
            delete mCountdownText;
            delete countdownTimer;

            mIsHost ? mPlayerMe->setFocus() : mPlayerEnemy->setFocus();
        }
        else
        {
            mCountdownText->setText(QString::number(countdown));
        }
    });
}
