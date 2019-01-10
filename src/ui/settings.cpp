#include "settings.h"
#include "ui_settings.h"

Settings::Settings(Config &cfg,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::settings)
{
/*    ui->setupUi(this);
    conf = cfg;

    QString fullScreanStr = cfg->get("fullScrean").at(0);
    if (fullScreanStr == "false")
    {
        ui->pushButton->setIcon(QIcon (":/icon/off.png"));
        fullScrean = false;
    }
    else if (fullScreanStr == "true")
    {
        fullScrean = true;
        ui->pushButton->setIcon(QIcon(":/icon/checkBox on.png"));
    }
    else if (fullScreanStr != "false" || "true")
    {
        //TODO
    }

    QString lenguageStr = cfg->get("lenguage").at(0);
    if (lenguageStr == "EN")
    {
        lenguage = 0;
        ui->lenguageComboBox->setCurrentIndex(0);
    }
    else if (lenguageStr == "RU")
    {
        lenguage = 1;
        ui->lenguageComboBox->setCurrentIndex(1);
    }
    else if (lenguageStr != "EN" || "RU")
    {
        //TODO
    }*/
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
/*    if (!fullScrean)
    {
        ui->pushButton->setIcon(QIcon(":/icon/checkBox on.png"));
        fullScrean = true;
    }else
    {
        ui->pushButton->setIcon(QIcon (":/icon/off.png"));
        fullScrean = false;
    }*/
}

void Settings::save()
{
    /*qDebug () << "save";
    //fullScrean
    QString fullScreanStr;
    if (fullScrean)
    {
        fullScreanStr = "true";
    }else{
        fullScreanStr = "false";
    }
    conf->set("fullScrean", fullScreanStr);
    //lenguage
    QString lenguageStr;
    switch (lenguage) {
    case 0:
        lenguageStr = "EN";
        break;
    case 1:
        lenguageStr = "RU";
        break;
    default:
        break;
    }
    conf->set("lenguage", lenguageStr);

    conf->save();
    close();*/
}

void Settings::on_lenguageComboBox_currentIndexChanged(int index)
{
    //lenguage = index;
}
