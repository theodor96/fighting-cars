#include "ui_AboutPopup.h"

#include "UserInterface/AboutPopup.h"
#include "Common/Constants.h"

#include <QDebug>

AboutPopup::AboutPopup(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AboutPopup)
{
    ui->setupUi(this);

    this->setFixedSize(ABOUT_POPUP_WIDTH, ABOUT_POPUP_HEIGHT);

    qDebug() << "ctor called";
}

AboutPopup::~AboutPopup()
{
    delete ui;
}
