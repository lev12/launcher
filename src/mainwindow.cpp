#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);

    cfgLauncher = &LauncherConfig::instance();
    mainMenu = new UiMainMenu();
    network = new Network(cfgLauncher->getServerAddress().host(),
                          cfgLauncher->getServerPort(),log);
    appCon = new ApplicationController (QString(".\\data"),network);
    activeFrame = new QFrame();
    ui->general->addWidget(mainMenu);
    setHomePage();

    connect(mainMenu,&UiMainMenu::clickedHomePage,this,&MainWindow::setHomePage);
    connect(homePage,&UiHomePage::clikedApplication,this,&MainWindow::setUiApplication);
    connect(mainMenu,&UiMainMenu::clickedSettings,this,&MainWindow::setSettings);

    if (cfgLauncher->getLogState() == Log::loggingAndSend)
    {
        log = new Log(cfgLauncher->getLogFolder());
        log->head();
    }

    /*this->setGeometry(100,100,cfgLauncher.get("width").at(0).toInt(),cfgLauncher.get("height").at(0).toInt());
    if (cfgLauncher.get("fullScrean").at(0) == "true")
    {
        this->showMaximized();
    }*/
}

MainWindow::~MainWindow()
{
    log->grabber(cfgLauncher->getCountLogFile());

    cfgLauncher->raedFile();
    cfgLauncher->setWidth(static_cast <unsigned short>(this->width()));
    cfgLauncher->setHeight(static_cast <unsigned short>(this->height()));
    cfgLauncher->setFullScrean(cfgLauncher->getFullScrean());
    cfgLauncher->save();

    delete ui;
}

void MainWindow::setSettings()
{
    removeActiveFrame();
    settings = new SettingWrapper (cfgLauncher);
    setActiveFrame(settings);
}

void MainWindow::setUiApplication(UiApplication *app)
{
    removeActiveFrame();
    setActiveFrame(app);
}

void MainWindow::setHomePage()
{
    removeActiveFrame();
    homePage = new UiHomePage (appCon->getAppList(),this);
    setActiveFrame(homePage);
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

void MainWindow::removeActiveFrame()
{
    ui->general->removeWidget(activeFrame);
    delete activeFrame;
    activeFrame = nullptr;
}

void MainWindow::setActiveFrame(QFrame *f)
{
    activeFrame = f;
    ui->general->addWidget(f);
}
