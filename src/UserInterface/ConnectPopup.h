#ifndef CONNECTPOPUP_H
#define CONNECTPOPUP_H

#include <QDialog>

namespace Ui
{
    class ConnectPopup;
}

class QCloseEvent;

class ConnectPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit ConnectPopup(QWidget* parent = nullptr);
    ~ConnectPopup();

    void gotAccept();
    void gotReject();

    void closeEvent(QCloseEvent*) override;

private:
    Ui::ConnectPopup* ui;
};

#endif // CONNECTPOPUP_H

