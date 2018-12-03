#include "uiApplicationOverview.h"
#include "ui_uiApplicationOverview.h"

UiApplicationOverview::UiApplicationOverview(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplicationOverview)
{
    ui->setupUi(this);
}

UiApplicationOverview::~UiApplicationOverview()
{
    delete ui;
}
