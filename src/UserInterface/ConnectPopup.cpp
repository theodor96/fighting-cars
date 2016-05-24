#include "ui_ConnectPopup.h"

#include "UserInterface/ConnectPopup.h"
#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"
#include "Network/PacketManager.h"

#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

ConnectPopup::ConnectPopup(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ConnectPopup)
{
    ui->setupUi(this);

    auto mainWindow = static_cast<MainWindow*>(parent);
    mainWindow->getPacketManager()->setParent(this);

    this->setFixedSize(CONNECT_POPUP_WIDTH, CONNECT_POPUP_WIDTH);



    QRegExp re("^(([1-9]?\\d|1\\d\\d|25[0-5]|2[0-4]\\d)\\.){3}([1-9]?\\d|1\\d\\d|25[0-5]|2[0-4]\\d)$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    ui->mIpLineEdit->setValidator(validator);

    this->connect(ui->mIpLineEdit, &QLineEdit::textChanged, this, [=]
    {
        int pos = 0;
        ui->mConnectBtn->setEnabled(validator->validate(ui->mIpLineEdit->text(), pos) == QValidator::Acceptable);
    });


    this->connect(ui->mConnectBtn, &QPushButton::clicked, this, [=]
    {
        mainWindow->getPacketManager()->setIPAddress(ui->mIpLineEdit->text());
        mainWindow->getPacketManager()->sendConnectRequest(mainWindow->getUsername());
    });
}

ConnectPopup::~ConnectPopup()
{
    delete ui;
}

void ConnectPopup::gotAccept()
{

}

void ConnectPopup::gotReject()
{

}


