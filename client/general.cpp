#include "general.h"
#include "ui_general.h"

General::General(QWidget *parent, Menu *menuGen) :
    QFrame(parent),
    ui(new Ui::General)
{
    ui->setupUi(this);
    cfg  = new config();
    menu = menuGen;

    appinfo.page = 0;
    appinfo.nameApp = "general";
    appinfo.widget = this;

    QString fullScreanStr = cfg->get("fullScrean");
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
        setting = new settings (ui->settingsLayout->widget(),cfg);
        connect(setting,SIGNAL(close()),
                this,SLOT(on_pushButton_clicked()));
        ui->settingsLayout->insertWidget(1,setting);
        showSettings = true;
    }
    else
    {
        ui->settingsLayout->removeWidget(setting);

        QString fullScreanStr = cfg->get("fullScrean");
        if (fullScreanStr == "false")
        {
            normalMode();
        }
        else if (fullScreanStr == "true")
        {
            fullScreenMode();
        }

        delete setting;
        showSettings = false;
    }
}

void General::on_pushButton_2_clicked()
{
    menu->setShowWidget(1);
}
