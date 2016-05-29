#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class MainWindow;

class GameEngine :
        public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(MainWindow*);
    ~GameEngine();

private:
    MainWindow* mParent;
};

#endif // GAMEENGINE_H

