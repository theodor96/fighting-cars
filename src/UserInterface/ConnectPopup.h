#ifndef CONNECTPOPUP_H
#define CONNECTPOPUP_H

#include <QDialog>

namespace Ui
{
    class ConnectPopup;
}

class ConnectPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit ConnectPopup(QWidget* parent = nullptr);
    ~ConnectPopup();

private:
    Ui::ConnectPopup* ui;
};

#endif // CONNECTPOPUP_H

