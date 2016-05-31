#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QVector>

class MainWindow;
class QGraphicsScene;
class QGraphicsView;
class Player;
class QTimer;
class QGraphicsPixmapItem;
class QGraphicsSimpleTextItem;

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

    void buildGui();
    void updateGui(int, bool);

private:
    MainWindow* mParent;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    Player* mPlayerMe;
    Player* mPlayerEnemy;
    bool mIsHost;
    QTimer* mBonusTimer;
    QGraphicsSimpleTextItem* mCountdownText;
    QVector<QGraphicsPixmapItem*> vLivesBlue;
    QVector<QGraphicsPixmapItem*> vLivesRed;

    quint32 getRandomBetween(quint32, quint32) const;
    void countdown();
};

#endif // GAMEENGINE_H

