#include "settingsmenu.h"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(QWidget *parent, config *conf, Log *logfile) :
    QFrame(parent),
    ui(new Ui::SettingsMenu)
{
    ui->setupUi(this);
    cfg = conf;
    log = logfile;
    setting = new settings(ui->verticalLayout->widget(),cfg);
    sendmessage = NULL;
    ui->pushButton_3->setText("save");
    ui->verticalLayout->addWidget(setting);
}

SettingsMenu::~SettingsMenu()
{
    delete ui;
}

void SettingsMenu::on_pushButton_2_clicked()
{
    if (setting == NULL)
    {
        setting = new settings(ui->verticalLayout->widget(),cfg);
        ui->verticalLayout->addWidget(setting);
        ui->pushButton_3->setText("save");
        delete sendmessage;
        sendmessage = NULL;
    }
}

void SettingsMenu::on_pushButton_clicked()
{
    if (sendmessage == NULL)
    {
        sendmessage = new SendMassage ();
        ui->verticalLayout->addWidget(sendmessage);
        ui->pushButton_3->setText("send");
        delete setting;
        setting = NULL;
    }
}

void SettingsMenu::on_pushButton_3_clicked()
{
    if (setting != NULL)
    {
        setting->save();
    }
    else if (sendmessage != NULL)
    {
        qDebug () << log;
        log->addMessage(sendmessage->getMessage());
    }

    ui->verticalLayout_4->removeWidget(sendmessage);
    ui->verticalLayout_4->removeWidget(setting);
    delete sendmessage;
    delete setting;
    close();
}

void SettingsMenu::on_pushButton_close_clicked()
{
    ui->verticalLayout_4->removeWidget(sendmessage);
    ui->verticalLayout_4->removeWidget(setting);
    delete sendmessage;
    delete setting;
    close();
}
