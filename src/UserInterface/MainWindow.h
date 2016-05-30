#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class PacketWriter;

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PacketWriter*);
    ~MainWindow();

    void setEnemyUsername(const QString&);
    const QString getEnemyUsername() const;

    PacketWriter* getPacketWriter() const;
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
    PacketWriter* mPacketWriter;
    bool mIsPlayClicked;
    QString mEnemyUsername;
};

#endif // USERINTERFACE_H
