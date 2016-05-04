#include "ui_userinterface.h"
#include <QMessageBox>

#include "UserInterface.h"
#include "Constants.h"






#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QDebug>

UserInterface::UserInterface(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    this->connect(ui->mActionNew, &QAction::triggered, this, []
    {
        //new game
    });

    this->connect(ui->mActionExit, &QAction::triggered, this, [=]
    {
        if (QMessageBox::question(this, WINDOW_TITLE, STR_ASK_EXIT, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            this->close();
        }
    });

    this->connect(ui->mActionAbout, &QAction::triggered, this, []
    {
        //about this
    });

    this->connect(ui->mActionAboutQt, &QAction::triggered, this, []
    {
        QApplication::aboutQt();
    });


    //ui->mWidget->close();
    //delete ui->mWidget;

    const QImage background(":/img/img/background.png");
    QLabel mylabel(this);
    mylabel.setGeometry(200, 200, 300, 300);
    mylabel.move(300, 300);
    mylabel.setText("test");
    //mylabel.setPixmap(QPixmap(":/img/background.png"));
    mylabel.show();
    //qDebug() << "a";

   /*
    QGraphicsScene* scene = new QGraphicsScene(0, 0, background.width(), background.height());
    QGraphicsView* view = new QGraphicsView(scene);
    scene->setBackgroundBrush(QBrush(background));
    view->setFixedSize(background.size());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();*/
}

UserInterface::~UserInterface()
{
    delete ui;
}
