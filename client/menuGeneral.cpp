#include "menuGeneral.h"
#include "ui_menuGeneral.h"

MenuGeneral::MenuGeneral(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MenuGeneral)
{
    ui->setupUi(this);
}

MenuGeneral::~MenuGeneral()
{
    delete ui;
}

void MenuGeneral::on_newsbutton_clicked()
{
    emit pushNews();
}

void MenuGeneral::on_aplicatonbutton_clicked()
{
    emit pushApplication();
}

void MenuGeneral::on_notificationbutton_clicked()
{
    emit pushNotification();
}

void MenuGeneral::on_downloadbutton_clicked()
{
    emit pushDownloads();
}

void MenuGeneral::on_settingbutton_clicked()
{
    emit pushSetting();
}

bool MenuGeneral::setUserName(QString name_str)
{
    ui->userlabel->setText(name_str);
    return true;
}
