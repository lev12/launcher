#ifndef VERSIONCONTROLLER_H
#define VERSIONCONTROLLER_H

#include <QString>
#include <QList>
#include <QFileInfo>
#include <QObject>

#include <stdexcept>

#include "globalVariable.h"
#include "versionInstall.h"
#include "versionNoInstall.h"
#include "network/network.h"

class VersionController : public QObject
{
    Q_OBJECT
public:
    VersionController(QDir &pathToFolderWithAllVersions, Network &network, QString &AppName);
    QList <AbstractVersion*> getFullListVersion();
    QStringList* getFullListVersionStrList();
    QList <VersionInstall*> getListInsallVersion();
    QList<VersionNoInstall*> getListVersionOnServer();
    AbstractVersion *getVersion(QString verName);

    bool deleteAllVersion();
    bool updateVersionsList();
    bool downloadVersion(VersionNoInstall ver);

    bool isFoundVersions ();
private:
    QList <AbstractVersion*> *versionsList;
    QDir *folderWithAllVersions;
    Network *net;
    QString *appName;

    bool initAppName (QString *name);
    bool initVersionController (QString &pathToFolder);
    bool initVersionsList();

    bool fillingVersionList(const QDir &verFolder);
    QList<AbstractVersion *> sortVersionList();

signals:
    void responseActualVersion (QString verName);
};

#endif // VERSIONCONTROLLER_H
