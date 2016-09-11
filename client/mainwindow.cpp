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

    cfg  = new config();
    menu = new Menu ();
    network = new Network();
    app = new ElectricalSimulator ();

    menu->addAppInfo(app->getAppInfo());
    QObject::connect(menu, SIGNAL (swithWidget()), this, SLOT(setWidgetApp ()));

    QObject::connect(network, SIGNAL (connectServer()), app, SLOT (connectServer()));
    QObject::connect(app, SIGNAL (getListVersions ()), network, SLOT (getVersionListOnServer (QString)));
    network->getVersionListOnServer("asd");

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
