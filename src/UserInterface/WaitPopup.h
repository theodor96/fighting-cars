#ifndef WAITPOPUP_H
#define WAITPOPUP_H

#include <QDialog>

namespace Ui
{
    class WaitPopup;
}

class QMovie;
class QCloseEvent;
class QMessageBox;

class WaitPopup :
        public QDialog
{
    Q_OBJECT

public:
    explicit WaitPopup(QWidget* parent = nullptr);
    ~WaitPopup();

    void gotConnectRequest(const QString&);
    void gotAckConfirmation();

    void closeEvent(QCloseEvent*) override;

private:
    Ui::WaitPopup* ui;
    QMovie* mMovie;
    QMessageBox* mMsgBox;
};

#endif // WAITPOPUP_H

