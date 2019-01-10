#include "settingLanguge.h"
#include "ui_settingLanguges.h"

SettingLanguge::SettingLanguge(SettingsGeneral *settingsGeneral, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingLanguges)
{
    ui->setupUi(this);
    language = new QLocale::Language;
}

SettingLanguge::~SettingLanguge()
{
    delete ui;
}
