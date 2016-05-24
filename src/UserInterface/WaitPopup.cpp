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
    qDebug() << "setted parent to null";
}

void WaitPopup::gotConnectRequest(const QString& enemyUsername)
{
    mMsgBox->setText(QString(STR_ASK_PLAY) + enemyUsername + "?");
    mMsgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if (mMsgBox->exec() == QMessageBox::Yes)
    {
        qDebug() << "game should start naw";
    }
    else
    {
        qDebug() << "declined req";
    }
}

void WaitPopup::closeEvent(QCloseEvent*)
{
    delete this;
}

void WaitPopup::gotCancelRequest()
{
    mMsgBox->button(QMessageBox::Yes)->setEnabled(false);
}
