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
    network = new Network(cfgLauncher->getServerAddress().host(),
                          cfgLauncher->getServerPort(),log);
    appCon = new ApplicationController (QString(".\\data"),network);

    mainMenu = new UiMainMenu();
    activeFrameIndex = new int;
    activeFramesList = new QList<AbstractWindow*> ();
    ui->general->addWidget(mainMenu);

    *activeFrameIndex = -1;
    mainMenu->enabledAllButton();
    mainMenu->setEnabledBackButton(false);
    setHomePage();

    connect(mainMenu,&UiMainMenu::clickedHomePage,this,&MainWindow::setHomePage);
    connect(mainMenu,&UiMainMenu::clickedSettings,this,&MainWindow::setSettings);
    connect(mainMenu,&UiMainMenu::clickedBack,this,&MainWindow::setBeforeFrame);
    connect(homePage,&UiHomePage::clikedApplication,this,&MainWindow::setUiApplication);

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
    addActiveFrame(settings);
    mainMenu->setEnabledSettings(false);
}

void MainWindow::setUiApplication(UiApplication *app)
{
    removeActiveFrame();
    addActiveFrame(app);
}

void MainWindow::setHomePage()
{
    removeActiveFrame();
    homePage = new UiHomePage (appCon->getAppList(),this);
    addActiveFrame(homePage);
    mainMenu->setEnabledHomePage(false);
}

void MainWindow::setBeforeFrame()
{
    setBeforeActiveFrame();
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
        updatelauncher = new DialogUpdateLauncher(this, QString::number(double(ver)));
        QObject::connect(updatelauncher, SIGNAL(download(QString,versionType,int)), network, SLOT(downloadVersion(QString,versionType,int)));
        updatelauncher->show();
    }

}

void MainWindow::removeActiveFrame()
{
    if (!activeFramesList->isEmpty())
    {
        mainMenu->enabledAllButton();
        ui->general->removeWidget(activeFrame);
        activeFrame->hide();
    }
}

void MainWindow::addActiveFrame(AbstractWindow *f)
{
    if (activeFramesList->length()-1 > *activeFrameIndex)
    {
        while (activeFramesList->length() != 0)
        {
            activeFramesList->pop_back();
        }
    }

    activeFramesList->operator<<(f);
    activeFrame = f;
    setActiveFrame (activeFrame);
    *activeFrameIndex = *activeFrameIndex + 1;
}

void MainWindow::setActiveFrame(QFrame *f)
{
    ui->general->addWidget(f);
}

void MainWindow::setBeforeActiveFrame()
{
    if (activeFramesList->length() > 1)
    {
        *activeFrameIndex = *activeFrameIndex - 1;
        removeActiveFrame();
        QFrame *f = activeFramesList->at(*activeFrameIndex);
        f->show();
        activeFrame = f;
        setActiveFrame (f);
    }
    if (*activeFrameIndex <= 0)
    {
        mainMenu->setEnabledBackButton(false);
    }
    else
    {
       mainMenu->setEnabledBackButton(true); 
    }
}
