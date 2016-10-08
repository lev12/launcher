#include "versionmanager.h"
#include "ui_versionmanager.h"

VersionManager::VersionManager(QString AppName,QStringList instVersions, QStringList netVersions) :
    ui(new Ui::VersionManager)
{
    ui->setupUi(this);
    initFiles (AppName);

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
        item->setBackground(QBrush(QColor(11, 58, 120),Qt::SolidPattern));
        item->setTextColor(QColor (255,255,255));
        ui->listWidget->addItem(item);
    }

    ui->listWidget->setCurrentItem(ui->listWidget->item(0));
    refreshActionButton();
}

void VersionManager::refreshVersionManager(QStringList Versions)
{
    ui->listWidget->clear();
    for (int i(0); i < Versions.length(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString(Versions.at(i)));
        item->setBackground(QBrush(QColor(11, 58, 120),Qt::SolidPattern));
        item->setTextColor(QColor (255,255,255));
        ui->listWidget->addItem(item);
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

void VersionManager::on_pushButton_action_clicked()
{
    currentVersion = ui->listWidget->currentItem()->text();
    QStringList name = ui->listWidget->currentItem()->text().split(" ");
    bool statVer = isInstall(name.at(0),name.at(1));

    if (statVer)
    {
        deleteVersion();
    }
    else
    {
        downloadVersion();
    }
}

void VersionManager::on_listWidget_clicked(const QModelIndex &index)
{
    refreshActionButton();
}

void VersionManager::refreshActionButton()
{
    currentVersion = ui->listWidget->currentItem()->text();
    QStringList name = ui->listWidget->currentItem()->text().split(" ");
    bool statVer = isInstall(name.at(0),name.at(1));

    if (statVer)
    {
        qDebug () << name.at(0);
        ui->pushButton_action->setIcon(QIcon(":/icon/trash.png"));
    }
    else
    {
        ui->pushButton_action->setIcon(QIcon(":/icon/download.png"));
    }
}
