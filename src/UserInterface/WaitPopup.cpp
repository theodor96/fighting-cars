#include "ui_WaitPopup.h"
#include <QMessageBox>

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
    mMovie(new QMovie(":/img/img/lol.gif"))
{
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
}

void WaitPopup::gotConnectRequest(const QString& enemyUsername)
{
    if (QMessageBox::question(this, WINDOW_TITLE, QString(STR_ASK_PLAY) + enemyUsername + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        //send to enemy 1 2
        qDebug() << "game should start naw";
        delete this;
    }
    else
    {
        //send to enemy 1 3
    }
}
