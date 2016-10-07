#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>
#include "global_variable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);

    QDir dir (".//");
    dir.mkdir("data");

    cfg  = new config();
    menu = new Menu ();
    network = new Network();
    app = new ElectricalSimulator (network);

    menu->addAppInfo(app->getAppInfo());
    QObject::connect(menu, SIGNAL (swithWidget()), this, SLOT(setWidgetApp ()));

    ui->general->addWidget(menu);
    ui->general->addWidget(app);

    this->setGeometry(100,100,cfg->get("width").toInt(),cfg->get("height").toInt());
}

MainWindow::~MainWindow()
{
    //delete ver;
    delete ui;
}

void MainWindow::setWidgetApp ()
{

    ui->general->removeWidget(app);

    ui->general->addWidget(app);
}
