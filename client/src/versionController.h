#ifndef VERSIONCONTROLLER_H
#define VERSIONCONTROLLER_H

#include <QString>
#include <QList>
#include <QFileInfo>
#include <QObject>

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
    QList <VersionNoInstall*> getListVersionOnServer();
    AbstractVersion *getVersion(QString verName);

    AbstractVersion *getActualVersion ();
    QString getActualVersionStr();
    VersionInstall *getLsatCurrentVersion();

    void setLastCurrentVesion (QString verName);

    bool deleteAllVersion();
    bool updateVersionsList();
    bool downloadVersion(VersionNoInstall ver);

    bool isFoundVersions ();
private:
    QList <AbstractVersion*> *versionsList;
    QFileInfo *folderWithAllVersions;
    Network *net;
    QString *appName;
    AbstractVersion *actualVersion;
    VersionInstall *lastCurrentVersion;

    bool initAppName (QString *name);
    bool initVersionController (QString &pathToFolder);
    bool initFolderWithAllVersions(QString pathToFolder);
    bool initVersionsList();
    bool initActualVersion();
    bool initLastCurrentVersion();

    bool fillingActualVersion();
    bool fillingVersionList();
    QList<AbstractVersion *> sortVersionList();

private slots:
    void setActualVersionNet (QList<NetworkData> *response);

signals:
    void responseActualVersion (QString verName);
};

#endif // VERSIONCONTROLLER_H
