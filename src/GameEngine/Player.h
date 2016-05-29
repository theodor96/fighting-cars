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
    Player(GameEngine*, bool isRed, bool isHost);
    ~Player();

    void setUsername(const QString&);

    void focusOutEvent(QFocusEvent*) override;

    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

    void gotShot();
    void shootBullet();

private:
	GameEngine* mGameEngine;
    QString mUsername;
    bool mIsRed;
    bool mIsEnemy;
    QTimer* mMovingTimer;
    quint16 mStep;
    QStack<Qt::Key> mPressedKeys;
    Qt::Key mOrientation;
    bool mHasBulletCooldown;

    bool isEventAllowed(QKeyEvent*);
    void move();
    ;
};

#endif // PLAYER_H

