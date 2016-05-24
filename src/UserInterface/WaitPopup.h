#ifndef WAITPOPUP_H
#define WAITPOPUP_H

#include <QDialog>

namespace Ui
{
    class WaitPopup;
}

class QMovie;

class WaitPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit WaitPopup(QWidget* parent = nullptr);
    ~WaitPopup();

    void gotConnectRequest(const QString&);

private:
    Ui::WaitPopup* ui;
    QMovie* mMovie;
};

#endif // WAITPOPUP_H

