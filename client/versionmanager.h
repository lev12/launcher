#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <QFrame>

#include <QList>
#include <QString>
#include <QFileInfo>

//#include "application.h"

namespace Ui {
class VersionManager;
}

class VersionManager : public QFrame
{
    Q_OBJECT

public:
    VersionManager(QStringList Versions);

    void refreshVersionManager(QStringList Versions);

    ~VersionManager();

private:
    QStringList versions;
    Ui::VersionManager *ui;
};

#endif // VERSIONMANAGER_H
