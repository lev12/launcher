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
    QObject::connect(network,  SIGNAL(connectServer()), this, SLOT(connectServerStat()));
    electricalsimulator = new ElectricalSimulator (network);
    general = new General (NULL,menu);

    menu->addAppInfo(general->getAppInfo());
    menu->addAppInfo(electricalsimulator->getAppInfo());
    QObject::connect(menu, SIGNAL (swithWidget()), this, SLOT(setWidgetApp()));
    QObject::connect(general, SIGNAL(fullScreenMode()), this, SLOT(setFullScreanMode()));
    QObject::connect(general, SIGNAL(normalMode()), this, SLOT(setNormalMode()));
    ui->general->addWidget(menu);
    menu->setShowWidget(cfg->get("page").toInt());

    this->setGeometry(100,100,cfg->get("width").toInt(),cfg->get("height").toInt());
    if (cfg->get("fullScrean") == "true")
    {
        this->showMaximized();
    }
}

MainWindow::~MainWindow()
{
    cfg->argumet->clear();
    cfg->name->clear();
    cfg->raedFile();
    cfg->set("page",QString::number(menu->showIndex));
    cfg->set("width", QString::number(this->width()));
    cfg->set("height", QString::number(this->height()));
    cfg->set("fullScrean", cfg->get("fullScrean"));
    cfg->save();

    delete ui;
}

void MainWindow::connectServerStat()
{
    menu->setStatusNet(true);
}

void MainWindow::setFullScreanMode()
{
    this->showMaximized();
}

void MainWindow::setNormalMode()
{
    this->showNormal();
}

void MainWindow::setWidgetApp ()
{
    static QWidget *removeWidget;
    static int removeIndex;
    ui->general->removeWidget(removeWidget);
    if (removeIndex == 0)
    {
        delete general;
        general = new General(NULL, menu);
        QObject::connect(general, SIGNAL(fullScreenMode()), this, SLOT(setFullScreanMode()));
        QObject::connect(general, SIGNAL(normalMode()), this, SLOT(setNormalMode()));
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
