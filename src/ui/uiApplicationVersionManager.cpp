#include "uiApplicationVersionManager.h"
#include "ui_uiApplicationVersionManager.h"

UiApplicationVersionManager::UiApplicationVersionManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplicationVersionManager)
{
    ui->setupUi(this);
}

UiApplicationVersionManager::~UiApplicationVersionManager()
{
    delete ui;
}
