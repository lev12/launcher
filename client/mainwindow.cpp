#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);

    QDir dir (".//");
    dir.mkdir("data");

    menu = new Menu ();
    network = new Network(log);
    menugeneral = new MenuGeneral();
    appCon = new ApplicationController (QString(".\\data"),network);
    ui->general->addWidget(menugeneral);
    ui->general->addWidget(appCon->getAppList()->at(0)->getUiApplication());
    //threadNet = new QThread (this);
    if (cfgLauncher.get("log").at(0) == "sendToTheServer")
    {
        log = new Log(cfgLauncher.get("logPath").at(0));
        log->head();
    }

    //network->getVersionList("Electrical_Simulator");
    //network->getVersion("Electrical_Simulator", "alpha_45");
    general = new General (NULL,menu,log);

    menu->addAppInfo(general->getAppInfo());
    //menu->addAppInfo(electricalsimulator->getAppInfo());
    //menu->addAppInfo(electricalassistant->getAppInfo());

    QObject::connect(menu, SIGNAL (swithWidget()), this, SLOT(setWidgetApp()));
    QObject::connect(general, SIGNAL(fullScreenMode()), this, SLOT(setFullScreanMode()));
    QObject::connect(general, SIGNAL(normalMode()), this, SLOT(setNormalMode()));

    //menu->setShowWidget(cfg->get("page").toInt());

    this->setGeometry(100,100,cfgLauncher.get("width").at(0).toInt(),cfgLauncher.get("height").at(0).toInt());
    if (cfgLauncher.get("fullScrean").at(0) == "true")
    {
        this->showMaximized();
    }

    //threadNet->start();
}

MainWindow::~MainWindow()
{
    log->end();
    log->compression();
    log->comressionEnd(QString(".//log/compression.bin"));
    log->grabber(cfgLauncher.get("countFileLog").at(0).toInt());

    cfgLauncher.configKeyValue->clear();
    cfgLauncher.configKeyName->clear();
    cfgLauncher.raedFile();
    cfgLauncher.set("page",QString::number(menu->showIndex));
    cfgLauncher.set("width", QString::number(this->width()));
    cfgLauncher.set("height", QString::number(this->height()));
    cfgLauncher.set("fullScrean", cfgLauncher.get("fullScrean").at(0));
    cfgLauncher.save();

    delete menu;
    //delete network;
    delete ui;
}

void MainWindow::disconnectServerStat()
{
    menu->setStatusNet(false);
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
        //electricalsimulator = new ElectricalSimulator(network);
    }
    removeWidget = menu->showApp;
    ui->general->addWidget(removeWidget);
    removeIndex = menu->showIndex;
}

void MainWindow::currentLauncherVer(float ver)
{
    bool isNewVer = false;

    if (ver > number_version_launcher)
    {
        isNewVer = true;

    }

    if (isNewVer)
    {
        qDebug () << "dfdfdsdsfdffggf>";
        updatelauncher = new DialogUpdateLauncher(this, QString::number(ver));
        QObject::connect(updatelauncher, SIGNAL(download(QString,versionType,int)), network, SLOT(downloadVersion(QString,versionType,int)));
        updatelauncher->show();
    }

}
