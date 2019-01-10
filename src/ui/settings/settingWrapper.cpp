#include "settingWrapper.h"
#include "ui_settingWrapper.h"

SettingWrapper::SettingWrapper(Config *config,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsWrapper)
{
    ui->setupUi(this);
    cfg = config;
    settingsGeneral = new SettingsGeneral (cfg,this);
    settinglanguges = new SettingLanguge (settingsGeneral,this);
    ui->stackedWidget->addWidget(settingsGeneral);
    ui->stackedWidget->addWidget(settinglanguges);
    connect(settinglanguges, SIGNAL(back()),ui->stackedWidget, SLOT(setCurrentIndex(int a = 0)));
    connect(settingsGeneral, SIGNAL(showSettingsLanguges()),ui->stackedWidget, SLOT(setCurrentIndex(int a = 1)));
}

SettingWrapper::~SettingWrapper()
{
    delete ui;
    delete settingsGeneral;
}
