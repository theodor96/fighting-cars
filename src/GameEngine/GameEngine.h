#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class MainWindow;
class QGraphicsScene;
class QGraphicsView;
class Player;
class QGraphicsItem;

class GameEngine :
        public QObject
{
    Q_OBJECT

public:
    GameEngine(MainWindow*, bool);
    ~GameEngine();

    MainWindow* getParent() const;
    void gotKeyPressed(Qt::Key);
    void gotKeyReleased(Qt::Key);

    void add(QGraphicsItem*);

private:
    MainWindow* mParent;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    Player* mPlayerMe;
    Player* mPlayerEnemy;
    bool mIsHost;
};

#endif // GAMEENGINE_H

