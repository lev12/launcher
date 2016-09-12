#include "general.h"
#include "ui_general.h"

General::General(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::General)
{
    ui->setupUi(this);
    cfg  = new config();

    QString fullScreanStr = cfg->get("fullScrean");
    if (fullScreanStr == "false")
    {
        //this->showNormal();
    }
    else if (fullScreanStr == "true")
    {
        //this->showMaximized();
    }

    /*if (!showSettings)
    {
        setting = new settings (ui->settingsLayout->widget(),cfg);
        connect(setting,SIGNAL(close()),
                this,SLOT(on_settingsButton_clicked()));
        ui->settingsLayout->insertWidget(1,setting);
        showSettings = true;
    }
    else
    {
        ui->settingsLayout->removeWidget(setting);

        QString fullScreanStr = cfg->get("fullScrean");
        if (fullScreanStr == "false")
        {
            this->showNormal();
        }
        else if (fullScreanStr == "true")
        {
            this->showMaximized();
        }

        delete setting;
        showSettings = false;
    }*/
}

General::~General()
{
    delete ui;
}
