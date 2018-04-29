#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <QFrame>

#include <QList>
#include <QString>
#include <QFileInfo>
#include <QPushButton>


namespace Ui {
class VersionManager;
}

class VersionManager : public QObject
{
    Q_OBJECT

public:
    VersionManager(QString AppName, QStringList instVersions, QStringList netVersions);

    void refreshVersionManager(QStringList Versions);
    QString currentVersion;

    ~VersionManager();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_action_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

signals:
    void closeButton();
    void downloadVersion();
    void deleteVersion();

private:
    QStringList versions;
    Ui::VersionManager *ui;

    void refreshActionButton();
};

#endif // VERSIONMANAGER_H
