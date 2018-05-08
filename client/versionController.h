#ifndef VERSIONCONTROLLER_H
#define VERSIONCONTROLLER_H

#include <QString>
#include <QList>
#include <QFileInfo>
#include <QObject>

#include "version.h"
#include "globalVariable.h"
#include "network/network.h"

class VersionController : public QObject
{
    Q_OBJECT
public:
    VersionController(QString *pathToFolderWithAllVersions, Network *g_net, QString *AppName);
    QList <Version*> getFullListVersion();
    QStringList* getFullListVersionStrList();
    QList <Version*> getListInsallVersion();
    QList <Version*> getListVersionOnServer();
    Version *getVersion(QString verName);

    Version *getActualVersion ();
    QString getActualVersionStr();
    Version *getLsatCurrentVersion();

    void setLastCurrentVesion (QString verName);

    bool deleteAllVersion();
    bool updateVersionsList();
    bool downloadVersion(Version ver);

    bool isFoundVersions ();
private:
    QList <Version*> *versionsList;
    QFileInfo *folderWithAllVersions;
    Network *net;
    QString *appName;
    Version *actualVersion;
    Version *lastCurrentVersion;

    bool initAppName (QString *name);
    bool initVersionController (QString *pathToFolder);
    bool initFolderWithAllVersions(QString *pathToFolder);
    bool initVersionsList();
    bool initActualVersion();
    bool initLastCurrentVersion();

    bool fillingActualVersion();
    bool fillingVersionList();
    QList<Version *> sortVersionList();

private slots:
    void setActualVersionNet (QStringList *response);

signals:
    void responseActualVersion (QString verName);
};

#endif // VERSIONCONTROLLER_H
