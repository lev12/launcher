#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setStatusNet(false);
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

void Menu::on_pushButtonElectricalAssistant_clicked()
{
    showApp = appinfo.at(2).widget;
    showIndex = 2;
    swithWidget();
}


void Menu::addAppInfo (appInfo info)
{
    appinfo << info;
}

bool Menu::setShowWidget (int i)
{
    showApp = appinfo.at(i).widget;
    showIndex = i;
    swithWidget();
}

void Menu::setStatusNet(bool stat)
{
    if (stat)
    {
        ui->line->setText("online");
        ui->line->setStyleSheet("color: rgb(46, 216, 60);\nfont: 75 italic 16pt Times New Roman;\nbackground-color: rgb(3, 4, 30, 60);");
    }
    else
    {
        ui->line->setText("offline");
        ui->line->setStyleSheet("color: rgb(255, 0, 0);\nfont: 75 italic 16pt Times New Roman;\nbackground-color: rgb(3, 4, 30, 60);");
    }
}

void Menu::on_LaunherPushButton_clicked()
{
    showApp = appinfo.at(0).widget;
    showIndex = 0;
    swithWidget();
}

void Menu::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl(appinfo.at(showIndex).webSite));
}

void Menu::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl(appinfo.at(showIndex).vk));
}

void Menu::on_pushButton_4_clicked()
{
    QDesktopServices::openUrl(QUrl(appinfo.at(showIndex).youtube));
}
