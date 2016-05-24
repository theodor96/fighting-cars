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

    PacketManager* getPacketManager() const;
    const QString getUsername() const;

private:
    void connectSignalsToSlots();
    template <typename PopupType>
    void makePopup()
    {
        qDebug() << "constructing a popup";
        auto popup = new PopupType(this);
        popup->setModal(true);
        popup->show();
    }

    Ui::MainWindow* ui;
    PacketManager* mPacketManager;
    bool mIsPlayClicked;
};

#endif // USERINTERFACE_H
