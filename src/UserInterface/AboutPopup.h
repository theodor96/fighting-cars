#ifndef ABOUTPOPUP_H
#define ABOUTPOPUP_H

#include <QDialog>

namespace Ui
{
    class AboutPopup;
}

class AboutPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit AboutPopup(QWidget* parent = nullptr);
    ~AboutPopup();

private:
    Ui::AboutPopup* ui;
};

#endif // ABOUTPOPUP_H

