#include "settingLanguges.h"
#include "ui_settingLanguges.h"

SettingLanguges::SettingLanguges(SettingsGeneral *settingsGeneral, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingLanguges)
{
    ui->setupUi(this);
    language = new QLocale::Language;
}

SettingLanguges::~SettingLanguges()
{
    delete ui;
}
