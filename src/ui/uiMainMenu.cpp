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

bool UiMainMenu::getEnableBackButton()
{
    return ui->backButton->isEnabled();
}

bool UiMainMenu::getEnableHomePage()
{
    return ui->homeButton->isEnabled();
}

bool UiMainMenu::getEnableSettings()
{
    return ui->settingButton->isEnabled();
}

void UiMainMenu::setEnabledBackButton(bool state)
{
    ui->backButton->setEnabled(state);
    return;
}

void UiMainMenu::setEnabledHomePage(bool state)
{
    ui->homeButton->setEnabled(state);
    return;
}

void UiMainMenu::setEnabledSettings(bool state)
{
    ui->settingButton->setEnabled(state);
    return;
}

void UiMainMenu::enabledAllButton()
{
    ui->backButton->setEnabled(true);
    ui->homeButton->setEnabled(true);
    ui->settingButton->setEnabled(true);
    ui->searchButton->setEnabled(true);
}

void UiMainMenu::disabledAllButton()
{
    ui->backButton->setEnabled(false);
    ui->homeButton->setEnabled(false);
    ui->settingButton->setEnabled(false);
    ui->searchButton->setEnabled(false);
}

void UiMainMenu::on_settingButton_clicked()
{
    clickedSettings();
}

void UiMainMenu::on_homeButton_clicked()
{
    clickedHomePage();
}

void UiMainMenu::on_backButton_clicked()
{
    clickedBack();
}
