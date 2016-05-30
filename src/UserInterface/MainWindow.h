#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class PacketManager;

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PacketManager*);
    ~MainWindow();

    void setEnemyUsername(const QString&);
    const QString getEnemyUsername() const;

    PacketManager* getPacketManager() const;
    const QString getUsername() const;

    void startGame(bool mIsHost);

private:
    void connectSignalsToSlots();
    template <typename PopupType>
    void makePopup()
    {
        auto popup = new PopupType(this);
        popup->setModal(true);
        popup->show();
    }

    Ui::MainWindow* ui;
    PacketManager* mPacketManager;
    bool mIsPlayClicked;
    QString mEnemyUsername;
};

#endif // USERINTERFACE_H
