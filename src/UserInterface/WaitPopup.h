#ifndef WAITPOPUP_H
#define WAITPOPUP_H

#include <QDialog>

namespace Ui
{
    class WaitPopup;
}

class WaitPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit WaitPopup(QWidget* parent = nullptr);
    ~WaitPopup();

private:
    Ui::WaitPopup* ui;
};

#endif // WAITPOPUP_H

