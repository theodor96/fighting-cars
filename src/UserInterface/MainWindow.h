#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

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
    bool mIsPlayClicked;
};

#endif // USERINTERFACE_H
