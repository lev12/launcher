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

    menugeneral = new MenuGeneral();
    network = new Network(log);
    appCon = new ApplicationController (QString(".\\data"),network);
    ui->general->addWidget(menugeneral);
    ui->general->addWidget(appCon->getAppList()->at(0)->getUiApplication());
    if (cfgLauncher.get("log").at(0) == "sendToTheServer")
    {
        log = new Log(cfgLauncher.get("logPath").at(0));
        log->head();
    }

    QObject::connect(general, SIGNAL(fullScreenMode()), this, SLOT(setFullScreanMode()));
    QObject::connect(general, SIGNAL(normalMode()), this, SLOT(setNormalMode()));


    this->setGeometry(100,100,cfgLauncher.get("width").at(0).toInt(),cfgLauncher.get("height").at(0).toInt());
    if (cfgLauncher.get("fullScrean").at(0) == "true")
    {
        this->showMaximized();
    }
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
    cfgLauncher.set("width", QString::number(this->width()));
    cfgLauncher.set("height", QString::number(this->height()));
    cfgLauncher.set("fullScrean", cfgLauncher.get("fullScrean").at(0));
    cfgLauncher.save();

    delete ui;
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
