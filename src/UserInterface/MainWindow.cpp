#include "ui_MainWindow.h"
#include <QMessageBox>

#include "UserInterface/MainWindow.h"
#include "Common/Constants.h"

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
//    this->connect(ui->mActionNew, &QAction::triggered, this, []
//    {
//        //new game
//    });

//    this->connect(ui->mActionExit, &QAction::triggered, this, [=]
//    {
//        if (QMessageBox::question(this, WINDOW_TITLE, STR_ASK_EXIT, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
//        {
//            this->close();
//        }
//    });

//    this->connect(ui->mActionAbout, &QAction::triggered, this, []
//    {
//        //about this
//    });

//    this->connect(ui->mActionAboutQt, &QAction::triggered, this, []
//    {
//        QApplication::aboutQt();
//    });
}
