#include "ui_MainWindow.h"
#include <QMessageBox>

#include "UserInterface/MainWindow.h"
#include "UserInterface/AboutPopup.h"
#include "UserInterface/ConnectPopup.h"
#include "UserInterface/WaitPopup.h"
#include "Network/PacketManager.h"
#include "Common/Constants.h"


#include <QPropertyAnimation>

#include <QDebug>

MainWindow::MainWindow(PacketManager* packetManager) :
    QMainWindow(),
    ui(new Ui::MainWindow),
    mPacketManager(packetManager),
    mIsPlayClicked(false)
{
    ui->setupUi(this);
    ui->mConnectBtn->hide();
    ui->mHostBtn->hide();

    this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    connectSignalsToSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

PacketManager* MainWindow::getPacketManager() const
{
    return mPacketManager;
}

const QString MainWindow::getUsername() const
{
    return ui->mUsernameLineEdit->text();
}

void MainWindow::connectSignalsToSlots()
{
    this->connect(ui->mPlayBtn, &QPushButton::clicked, this, [=]
    {
        if (mIsPlayClicked)
        {
            return;
        }

        mIsPlayClicked = true;
        QPropertyAnimation* animation = new QPropertyAnimation(ui->mBtnsContainer, "geometry");
        this->connect(animation, &QPropertyAnimation::finished, this, [=]
        {
            ui->mConnectBtn->show();
            ui->mHostBtn->show();
        });
        auto beginPosition = ui->mBtnsContainer->geometry();

        animation->setDuration(400);
        animation->setStartValue(beginPosition);
        animation->setEndValue(QRect(beginPosition.topLeft() + QPoint(0, 60), ui->mBtnsContainer->size()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);

    });

    this->connect(ui->mQuitBtn, &QPushButton::clicked, this, [=]
    {
        if (QMessageBox::question(this, WINDOW_TITLE, STR_ASK_EXIT, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            this->close();
        }
    });

    this->connect(ui->mAboutBtn, &QPushButton::clicked, this, [=]
    {
        makePopup<AboutPopup>();
    });

    this->connect(ui->mUsernameLineEdit, &QLineEdit::textChanged, this, [=]
    {
        ui->mPlayBtn->setEnabled(ui->mUsernameLineEdit->text().length() >= USERNAME_MIN_CHARACTERS);
    });

    this->connect(ui->mConnectBtn, &QPushButton::clicked, this, [=]
    {
        makePopup<ConnectPopup>();
    });

    this->connect(ui->mHostBtn, &QPushButton::clicked, this, [=]
    {
        qDebug() << "making wait popup";
        makePopup<WaitPopup>();
    });
}


