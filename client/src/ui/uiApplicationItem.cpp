#include "uiApplicationItem.h"
#include "ui_uiApplicationItem.h"

UiApplicationItem::UiApplicationItem(QString &name, QIcon &icon, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplicationItem)
{
    ui->setupUi(this);

    appName = new QString (name);
    appIcon = new QIcon (icon);

    ui->applicationButton->setIcon(*appIcon);
    ui->applicationName->setText(*appName);
}

UiApplicationItem::~UiApplicationItem()
{
    delete ui;
}

QString *UiApplicationItem::getAppName() const
{
    return appName;
}

QIcon *UiApplicationItem::getAppIcon() const
{
    return appIcon;
}

void UiApplicationItem::on_applicationButton_clicked()
{
    clicked(this);
}
