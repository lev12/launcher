#include "settingsGeneral.h"
#include "ui_settingsGeneral.h"

SettingsGeneral::SettingsGeneral(Config *config, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsGeneral)
{
    ui->setupUi(this);
}

SettingsGeneral::~SettingsGeneral()
{
    delete ui;
}
