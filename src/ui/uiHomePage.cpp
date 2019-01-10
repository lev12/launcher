#include "uiHomePage.h"
#include "ui_uiHomePage.h"

UiHomePage::UiHomePage(QList<AbstractApplication*> applist, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiHomePage)
{
    ui->setupUi(this);
    applicationMap = new QMap<AbstractApplication*,UiApplicationItem*>;
    applicationlist = new QList<AbstractApplication*>;
    applicationlist = &applist;
    foreach (AbstractApplication* item, *applicationlist)
    {
        UiApplicationItem *appitem = item->getUiApplicationItem();
        qDebug () << appitem->getAppName();

        ui->gridLayout->addWidget(appitem);
        applicationMap->insert(item,appitem);
        connect(appitem,&UiApplicationItem::clicked,this,&UiHomePage::reciveClicked);
    }
}

UiHomePage::~UiHomePage()
{
    delete ui;
}

void UiHomePage::reciveClicked(UiApplicationItem *app)
{
    clikedApplication(applicationMap->key(app)->getUiApplication());
}
