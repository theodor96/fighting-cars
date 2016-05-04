#include "userinterface.h"
#include "ui_userinterface.h"

UserInterface::UserInterface(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

UserInterface::~UserInterface()
{
    delete ui;
}
