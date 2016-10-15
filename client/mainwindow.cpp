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
    electricalsimulator = new ElectricalSimulator (network);
    general = new General ();

    menu->addAppInfo(general->getAppInfo());
    menu->addAppInfo(electricalsimulator->getAppInfo());

    QObject::connect(menu, SIGNAL (swithWidget()), this, SLOT(setWidgetApp()));

    ui->general->addWidget(menu);

    this->setGeometry(100,100,cfg->get("width").toInt(),cfg->get("height").toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWidgetApp ()
{
    static QWidget *removeWidget;
    static int removeIndex;
    ui->general->removeWidget(removeWidget);
    if (removeIndex == 0)
    {
        delete general;
        general = new General();
    }

    if (removeIndex == 1)
    {
        delete electricalsimulator;
        electricalsimulator = new ElectricalSimulator(network);
    }
    removeWidget = menu->showApp;
    ui->general->addWidget(removeWidget);
    removeIndex = menu->showIndex;
}
