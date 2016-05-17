#include "ui_ConnectPopup.h"

#include "UserInterface/ConnectPopup.h"
#include "Common/Constants.h"

#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

ConnectPopup::ConnectPopup(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ConnectPopup)
{
    ui->setupUi(this);

    this->setFixedSize(CONNECT_POPUP_WIDTH, CONNECT_POPUP_WIDTH);



    QRegExp re("^(([1-9]?\\d|1\\d\\d|25[0-5]|2[0-4]\\d)\\.){3}([1-9]?\\d|1\\d\\d|25[0-5]|2[0-4]\\d)$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    ui->mIpLineEdit->setValidator(validator);

    this->connect(ui->mIpLineEdit, &QLineEdit::textChanged, this, [=]
    {

        int pos = 0;
        ui->mConnectBtn->setEnabled(validator->validate(ui->mIpLineEdit->text(), pos) == QValidator::Acceptable);
    });
}

ConnectPopup::~ConnectPopup()
{
    delete ui;
}


