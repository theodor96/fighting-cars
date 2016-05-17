#include "ui_WaitPopup.h"

#include "UserInterface/WaitPopup.h"
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
}

WaitPopup::~WaitPopup()
{
    delete ui;
}
