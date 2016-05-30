#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class PacketWriter;
class PacketReader;

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PacketWriter*, PacketReader*);
    ~MainWindow();

    void setEnemyUsername(const QString&);
    const QString getEnemyUsername() const;

    PacketWriter* getPacketWriter() const;
    PacketReader* getPacketReader() const;
    const QString getUsername() const;

    void startGame(bool mIsHost);

    void reparentPacketReader(QObject*);

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
    PacketReader* mPacketReader;
    bool mIsPlayClicked;
    QString mEnemyUsername;
};

#endif // USERINTERFACE_H
