#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QStack>

class GameEngine;
class QKeyEvent;
class QTimer;

class Player :
        public QGraphicsPixmapItem

{

public:
    Player(GameEngine*, bool isEnemy, bool isHost);
    ~Player();

    void setUsername(const QString&);

    void focusOutEvent(QFocusEvent*) override;

    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

    void gotShot();

private:
	GameEngine* mGameEngine;
    QString mUsername;
    bool mIsEnemy;
    QTimer* mMovingTimer;
    quint16 mStep;
    QStack<Qt::Key> mPressedKeys;
    Qt::Key mOrientation;

    bool isEventAllowed(QKeyEvent*);
    void move();
    void shootBullet();
};

#endif // PLAYER_H

