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

    cfg = new config();
    menu = new Menu ();
    //threadNet = new QThread (this);
    if (cfg->get("log") == "sendToTheServer")
    {
        log = new Log(cfg->get("logPath"));
        log->head();
    }
    network = new Network(log);
    network->getVersion("Electrical_Simulator", "alpha_45");
    QObject::connect(log, SIGNAL(comressionEnd(QString)), network, SLOT(sendLog(QString)));
    QObject::connect(network, SIGNAL(connectServer()), this, SLOT(connectServerStat()));
    QObject::connect(network, SIGNAL(listVersions()), network, SLOT(getClv()));
    QObject::connect(network, SIGNAL(clv(float)), this, SLOT(currentLauncherVer(float)));
    QObject::connect(network, SIGNAL(disConnectServer()), this, SLOT(disconnectServerStat()));
    //QObject::connect(network->server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(netError(QAbstractSocket::SocketError)));
    //network->moveToThread(threadNet);
    //QObject::connect(this, SIGNAL(destroyed(QObject*)), threadNet, SLOT(quit()));

    electricalassistant = new ElectricalAssistant (network);
    electricalsimulator = new ElectricalSimulator (network);
    qDebug () << log;
    general = new General (NULL,menu,log);

    menu->addAppInfo(general->getAppInfo());
    menu->addAppInfo(electricalsimulator->getAppInfo());
    menu->addAppInfo(electricalassistant->getAppInfo());

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

    //threadNet->start();
}

MainWindow::~MainWindow()
{
    log->end();
    log->compression();
    log->comressionEnd(QString(".//log/compression.bin"));
    log->grabber(cfg->get("countFileLog").toInt());

    cfg->argumet->clear();
    cfg->name->clear();
    cfg->raedFile();
    cfg->set("page",QString::number(menu->showIndex));
    cfg->set("width", QString::number(this->width()));
    cfg->set("height", QString::number(this->height()));
    cfg->set("fullScrean", cfg->get("fullScrean"));
    cfg->save();

    delete cfg;
    delete electricalsimulator;
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

// Error net
void MainWindow::netError(QAbstractSocket::SocketError)
{
    log->print(network->server->errorString(), Log::error);
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
