#include "versionmanager.h"
#include "ui_versionmanager.h"

VersionManager::VersionManager(QStringList instVersions, QStringList netVersions) :
    ui(new Ui::VersionManager)
{
    ui->setupUi(this);

    versions = instVersions;

    for (int i(0); i < netVersions.length(); i++)
    {
        bool isItem = false;

        for (int a(0); a < instVersions.length(); a++)
        {
            if (netVersions.at(i) == instVersions.at(a))
            {
                isItem = true;
                break;
            }
        }

        if (!isItem)
        {
            versions << netVersions.at(i);
        }
    }

    for (int i(0); i < versions.length(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString(versions.at(i)));
        item->setBackground(QBrush(QColor(61,185,108),Qt::SolidPattern));
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

void VersionManager::on_pushButton_clicked()
{
    closeButton();
}
