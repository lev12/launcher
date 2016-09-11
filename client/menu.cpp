#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButtonElectricalSimulator_clicked()
{
    showApp = appinfo.at(0);
    swithWidget();
}

void Menu::addAppInfo (appInfo info)
{
    appinfo << info;
}
