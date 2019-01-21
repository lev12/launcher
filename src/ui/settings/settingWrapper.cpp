#include "settingWrapper.h"
#include "ui_settingWrapper.h"

SettingWrapper::SettingWrapper(LauncherConfig *config, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsWrapper)
{
    ui->setupUi(this);
    cfg = config;
    activeWidget = new QFrame;
    showGeneralSettings();
}

SettingWrapper::~SettingWrapper()
{
    delete ui;
    delete settingsGeneral;
}

void SettingWrapper::showGeneralSettings()
{
    delete activeWidget;
    settingsGeneral = new SettingsGeneral (this);
    ui->scrollArea->setWidget(settingsGeneral);
    connect(settingsGeneral, &SettingsGeneral::showSettingsLanguges, this, &SettingWrapper::showLauncherSetting);
    activeWidget = settingsGeneral;
}

void SettingWrapper::showLauncherSetting()
{
    delete activeWidget;
    settinglanguges = new SettingLanguge (settingsGeneral,this);
    ui->scrollArea->setWidget(settinglanguges);
    connect(settinglanguges, &SettingLanguge::back, this, &SettingWrapper::showGeneralSettings);
    activeWidget = settinglanguges;
    ui->horizontalLayout->addWidget(settingsGeneral);
}
