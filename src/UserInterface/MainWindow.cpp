#include "ui_MainWindow.h"
#include <QMessageBox>

#include "UserInterface/MainWindow.h"
#include "UserInterface/AboutPopup.h"
#include "Common/Constants.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    connectSignalsToSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalsToSlots()
{
    this->connect(ui->mPlayBtn, &QPushButton::clicked, this, []
    {
        //
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
        auto aboutPopup = new AboutPopup(this);
        aboutPopup->setModal(true);
        aboutPopup->show();
    });
}
