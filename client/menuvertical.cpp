#include "menuvertical.h"
#include "ui_menuvertical.h"

MenuVertical::MenuVertical(QFrame *parent) :
    QFrame(parent),
    ui(new Ui::MenuVertical)
{
    ui->setupUi(this);
}

MenuVertical::~MenuVertical()
{
    delete ui;
}

bool MenuVertical::setQuickStartText(QString str)
{
    ui->quickstartbutton->setText(str);
    return true;
}

void MenuVertical::on_generalbutton_clicked()
{
    emit pushGeneral();
}

void MenuVertical::on_versionmenagerbutton_clicked()
{
    emit pushVersionMenager();
}

void MenuVertical::on_settingbutton_clicked()
{
    emit pushSettings();
}

void MenuVertical::on_quickstartbutton_clicked()
{
    emit pushQuickStart();
}
