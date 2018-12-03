#include "uiApplicationInstalled.h"
#include "ui_uiApplicationInstalled.h"

UiApplicationInstalled::UiApplicationInstalled(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplicationInstalled)
{
    ui->setupUi(this);
}

UiApplicationInstalled::~UiApplicationInstalled()
{
    delete ui;
}
