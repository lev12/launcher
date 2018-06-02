#include "general.h"
#include "ui_general.h"

General::General(QWidget *parent, Menu *menuGen, Log *logfile) :
    QFrame(parent),
    ui(new Ui::General)
{
    ui->setupUi(this);
    menu = menuGen;
    if (logfile != NULL)
    {
        log = logfile;
        qDebug () << logfile << " general";

    }


    appinfo.page = 0;
    appinfo.nameApp = "general";
    appinfo.widget = this;
    appinfo.webSite = "";
    appinfo.vk = "";
    appinfo.youtube = "";

    QString fullScreanStr = cfgLauncher.get("fullScrean").at(0);
    if (fullScreanStr == "false")
    {
        normalMode();
    }
    else if (fullScreanStr == "true")
    {
        fullScreenMode();
    }
}

appInfo General::getAppInfo()
{
    return appinfo;
}

General::~General()
{
    delete ui;
}

void General::on_pushButton_clicked()
{
    if (!showSettings)
    {
        qDebug () << log;
        settingMenu = new SettingsMenu (ui->settingsLayout->widget(), &cfgLauncher, log);
        QObject::connect(settingMenu, SIGNAL(close()), this, SLOT(closeSettingsMenu()));
        ui->settingsLayout->insertWidget(1,settingMenu);
        showSettings = true;
    }
    else
    {
        qDebug () << "remove widget";
        ui->settingsLayout->removeWidget(settingMenu);

        QString fullScreanStr = cfgLauncher.get("fullScrean").at(0);
        if (fullScreanStr == "false")
        {
            normalMode();
        }
        else if (fullScreanStr == "true")
        {
            fullScreenMode();
        }

        delete settingMenu;
        showSettings = false;
    }
}

void General::closeSettingsMenu()
{
    qDebug () << "remove widget";
    ui->settingsLayout->removeWidget(settingMenu);

    QString fullScreanStr = cfgLauncher.get("fullScrean").at(0);
    if (fullScreanStr == "false")
    {
        normalMode();
    }
    else if (fullScreanStr == "true")
    {
        fullScreenMode();
    }

    delete settingMenu;
    showSettings = false;
}

void General::on_pushButton_2_clicked()
{
    menu->setShowWidget(2);
}

void General::on_pushButton_4_clicked()
{
    menu->setShowWidget(1);
}
