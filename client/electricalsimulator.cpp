#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(QWidget *parent)  :
    QFrame(parent),
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);
    cfg  = new config();

    appinfo.nameApp = "ElectricalSimulator";
    appinfo.widget  = ;
    appinfo.vk      = "vk.com";
    appinfo.youtube = "youtube.com";
    appinfo.webSite = "NULL";

    QString fullScreanStr = cfg->get("fullScrean");
    if (fullScreanStr == "false")
    {
        this->showNormal();
    }
    else if (fullScreanStr == "true")
    {
        this->showMaximized();
    }
}

ElectricalSimulator::~ElectricalSimulator()
{
    delete ui;
}

void ElectricalSimulator::on_refreshButton_clicked()
{

}

void ElectricalSimulator::on_pushButton_clicked()
{
    //ver->open();
}

void ElectricalSimulator::on_folderButton_clicked()
{
    QFileInfo openFile (".//data");
    QString openPath ("file:///");
    openPath.append(openFile.absoluteFilePath());
    QDesktopServices::openUrl(QUrl(openPath, QUrl::TolerantMode));
}

void ElectricalSimulator::on_settingsButton_clicked()
{
    if (!showSettings)
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
    }
}

appInfo ElectricalSimulator::getAppInfo()
{
    return appinfo;
}
