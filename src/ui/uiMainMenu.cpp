#include "uiMainMenu.h"
#include "ui_uiMainMenu.h"

UiMainMenu::UiMainMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiMainMenu)
{
    ui->setupUi(this);
}

UiMainMenu::~UiMainMenu()
{
    delete ui;
}

void UiMainMenu::on_homebutton_clicked()
{
    clickedHomePage();
}

void UiMainMenu::on_installedApplicatonButton_clicked()
{
    clickedInstalledApplication();
}

void UiMainMenu::on_settingbutton_clicked()
{
    clickedSettings();
}
