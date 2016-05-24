#include "ui_WaitPopup.h"
#include <QMessageBox>
#include <QAbstractButton>

#include "UserInterface/WaitPopup.h"
#include "UserInterface/MainWindow.h"
#include "Network/PacketManager.h"
#include "Common/Constants.h"

#include <QDebug>
#include <QMovie>
#include <QLabel>

WaitPopup::WaitPopup(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::WaitPopup),
    mMovie(new QMovie(":/img/img/lol.gif")),
    mMsgBox(new QMessageBox(this))
{
    qDebug() << "constructing wait popup";

    ui->setupUi(this);

    this->setFixedSize(WAIT_POPUP_WIDTH, WAIT_POPUP_HEIGHT);

    ui->mWaitingLabelImage->setMovie(mMovie);
    mMovie->start();

    static_cast<MainWindow*>(parent)->getPacketManager()->setParent(this);
}

WaitPopup::~WaitPopup()
{
    delete ui;
    delete mMovie;
    static_cast<MainWindow*>(this->parent())->getPacketManager()->setParent(nullptr);
}

void WaitPopup::gotConnectRequest(const QString& enemyUsername)
{
    if (QMessageBox::question(this, WINDOW_TITLE, QString(STR_ASK_PLAY) + enemyUsername + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        auto mainWindow = static_cast<MainWindow*>(this->parent());
        mainWindow->getPacketManager()->sendAccept(mainWindow->getUsername());
    }
    else
    {
        static_cast<MainWindow*>(this->parent())->getPacketManager()->sendReject();
    }
}

void WaitPopup::gotAckConfirmation()
{
    //porneste jocul
    qDebug() << "start game-wait";
    this->close();
}

void WaitPopup::closeEvent(QCloseEvent*)
{
    delete this;
}
