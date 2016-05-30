#include "ui_WaitPopup.h"
#include <QMessageBox>
#include <QAbstractButton>

#include "UserInterface/WaitPopup.h"
#include "UserInterface/MainWindow.h"
#include "Network/PacketWriter.h"
#include "Network/PacketReader.h"
#include "Common/Constants.h"

#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <QTimer>

WaitPopup::WaitPopup(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::WaitPopup),
    mMovie(new QMovie(":/img/img/lol.gif")),
    mMsgBox(new QMessageBox(this))
{
    ui->setupUi(this);
    this->setFixedSize(WAIT_POPUP_WIDTH, WAIT_POPUP_HEIGHT);

    ui->mWaitingLabelImage->setMovie(mMovie);
    mMovie->start();

    auto packetReader = static_cast<MainWindow*>(parent)->getPacketReader();
    packetReader->setParent(this);
    packetReader->startListening();
}

WaitPopup::~WaitPopup()
{
    delete ui;
    delete mMovie;
    static_cast<MainWindow*>(this->parent())->reparentPacketReader(nullptr);
    static_cast<MainWindow*>(this->parent())->getPacketReader()->stopListening();
}

void WaitPopup::gotConnectRequest(const QString& enemyUsername)
{
    auto mainWindow = static_cast<MainWindow*>(this->parent());
    mainWindow->getPacketWriter()->sendReceived();

    if (QMessageBox::question(this, WINDOW_TITLE, QString(STR_ASK_PLAY) + enemyUsername + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        mainWindow->getPacketWriter()->sendAccept(mainWindow->getUsername());
        QTimer* timer = new QTimer(this);
        timer->singleShot(1000, this, [=]
        {
            ui->mWaitingLabelText->setText(STR_RESP_DECLINED);
            delete timer;
        });
    }
    else
    {
        static_cast<MainWindow*>(this->parent())->getPacketWriter()->sendReject();
    }
}

void WaitPopup::gotAckConfirmation()
{
    MainWindow* mainWindow = static_cast<MainWindow*>(this->parent());
    this->close();
    mainWindow->startGame(true);
}

void WaitPopup::closeEvent(QCloseEvent*)
{
    delete this;
}
