#include "settingsmenu.h"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(QWidget *parent, config *conf) :
    QFrame(parent),
    ui(new Ui::SettingsMenu)
{
    ui->setupUi(this);
    cfg = conf;
    qDebug () << "assddda";
    setting = new settings(ui->verticalLayout_4->widget(),cfg);
    sendmessage = NULL;

    ui->verticalLayout_4->addWidget(setting, 1);
}

SettingsMenu::~SettingsMenu()
{
    delete ui;
}

void SettingsMenu::on_pushButton_2_clicked()
{
    if (setting == NULL)
    {
        setting = new settings(ui->verticalLayout_4->widget(),cfg);
        ui->verticalLayout_4->addWidget(setting, 1);
        connect(setting, SIGNAL(closeSettings()), this, SLOT(closePressButton()));
        delete sendmessage;
        sendmessage = NULL;
    }
}

void SettingsMenu::on_pushButton_clicked()
{
    if (sendmessage == NULL)
    {
        sendmessage = new SendMassage ();
        ui->verticalLayout_4->addWidget(sendmessage, 1);
        connect(sendmessage, SIGNAL(closeSendMassage()),this, SLOT(closePressButton()));
        delete setting;
        setting = NULL;
    }
}

void SettingsMenu::closePressButton()
{
    ui->verticalLayout_4->removeWidget(sendmessage);
    ui->verticalLayout_4->removeWidget(setting);
    delete sendmessage;
    delete setting;
    close();
}
