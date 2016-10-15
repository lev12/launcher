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
    showApp = appinfo.at(1).widget;
    showIndex = 1;
    swithWidget();
}

void Menu::addAppInfo (appInfo info)
{
    appinfo << info;
}

bool Menu::setShowWiget (int i)
{
    showApp = appinfo.at(i).widget;
    swithWidget();
}

void Menu::on_LaunherPushButton_clicked()
{
    showApp = appinfo.at(0).widget;
    showIndex = 0;
    swithWidget();
}
