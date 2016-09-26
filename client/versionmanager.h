#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <QFrame>

#include <QList>
#include <QString>
#include <QFileInfo>

#include "files.h"

namespace Ui {
class VersionManager;
}

class VersionManager : public Files
{
    Q_OBJECT

public:
    VersionManager(QStringList instVersions, QStringList netVersions);

    void refreshVersionManager(QStringList Versions);

    ~VersionManager();

private slots:
    void on_pushButton_clicked();

signals:
    void closeButton();

private:
    QStringList versions;
    Ui::VersionManager *ui;
};

#endif // VERSIONMANAGER_H
