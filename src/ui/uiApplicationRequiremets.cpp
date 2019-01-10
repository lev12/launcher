#include "uiApplicationRequiremets.h"
#include "ui_uiApplicationRequiremets.h"

UiApplicationRequiremets::UiApplicationRequiremets(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplicationRequiremets)
{
    ui->setupUi(this);
}

UiApplicationRequiremets::~UiApplicationRequiremets()
{
    delete ui;
}
