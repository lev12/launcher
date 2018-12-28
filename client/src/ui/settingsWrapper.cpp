#include "settingsWrapper.h"
#include "ui_settingsWrapper.h"

SettingsWrapper::SettingsWrapper(Config *config,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsWrapper)
{
    ui->setupUi(this);
    cfg = config;
    settingsGeneral = new SettingsGeneral (cfg,this);
    settinglanguges = new SettingLanguges (settingsGeneral,this);
    ui->stackedWidget->addWidget(settingsGeneral);
    ui->stackedWidget->addWidget(settinglanguges);
    connect(settinglanguges, SIGNAL(back()),ui->stackedWidget, SLOT(setCurrentIndex(int a = 0)));
    connect(settingsGeneral, SIGNAL(showSettingsLanguges()),ui->stackedWidget, SLOT(setCurrentIndex(int a = 1)));
}

SettingsWrapper::~SettingsWrapper()
{
    delete ui;
    delete settingsGeneral;
}
