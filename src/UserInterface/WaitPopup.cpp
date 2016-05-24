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
    ui(new Ui::WaitPopup)
{
    ui->setupUi(this);

    this->setFixedSize(WAIT_POPUP_WIDTH, WAIT_POPUP_HEIGHT);

    QMovie* movie = new QMovie(":/img/img/lol.gif");
    ui->mWaitingLabelImage->setMovie(movie);
    movie->start();

    static_cast<MainWindow*>(parent)->getPacketManager()->setParent(this);
}

WaitPopup::~WaitPopup()
{
    delete ui;
}

void WaitPopup::gotConnectRequest(const QString& enemyUsername)
{
    if (QMessageBox::question(this, WINDOW_TITLE, QString(STR_ASK_PLAY) + enemyUsername + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        //send to enemy 1 2
        qDebug() << "game should start naw";
    }
    else
    {
        //send to enemy 1 3
    }
}
