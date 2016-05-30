#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class MainWindow;
class QGraphicsScene;
class QGraphicsView;
class Player;
class QTimer;

class GameEngine :
        public QObject
{
    Q_OBJECT

public:
    GameEngine(MainWindow*, bool);
    ~GameEngine();

    MainWindow* getParent() const;
    void gotKeyPressed(Qt::Key);
    void gotKeyReleased(Qt::Key, const QPointF&);

    void gotShootBullet();
    void spawnBonus(quint32, const QPointF&);

private:
    MainWindow* mParent;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    Player* mPlayerMe;
    Player* mPlayerEnemy;
    bool mIsHost;
    QTimer* mBonusTimer;

    quint32 getRandomBetween(quint32, quint32) const;
};

#endif // GAMEENGINE_H

