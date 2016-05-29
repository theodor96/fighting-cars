#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class MainWindow;
class QGraphicsScene;
class QGraphicsView;
class Player;

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

private:
    MainWindow* mParent;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    Player* mPlayerMe;
    Player* mPlayerEnemy;
};

#endif // GAMEENGINE_H

