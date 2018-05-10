#include "uiApplicationItem.h"
#include "ui_uiApplicationItem.h"

uiApplicationItem::uiApplicationItem(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::uiApplicationItem)
{
    ui->setupUi(this);
}

uiApplicationItem::~uiApplicationItem()
{
    delete ui;
}
