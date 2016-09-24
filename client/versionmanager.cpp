#include "versionmanager.h"
#include "ui_versionmanager.h"

VersionManager::VersionManager(QStringList Versions) :
    ui(new Ui::VersionManager)
{
    ui->setupUi(this);

    versions = Versions;
    for (int i(0); i < versions.length(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString(versions.at(i)));
        item->setBackground(QBrush(QColor(255,0,0),Qt::SolidPattern));
        item->setTextColor(QColor (255,255,255));
        ui->listWidget->addItem(item);
    }
}

void VersionManager::refreshVersionManager(QStringList Versions)
{
    for (int i(0); i < Versions.length(); i++)
    {
        QListWidgetItem item (QString(Versions.at(i)));
        item.setBackground(QBrush(QColor(255,0,0),Qt::SolidPattern));
        ui->listWidget->addItem(&item);
    }
}

VersionManager::~VersionManager()
{
    delete ui;
}
