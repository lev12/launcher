#ifndef VERSIONCONTROLLER_H
#define VERSIONCONTROLLER_H

#include <QString>
#include <QList>
#include <QFileInfo>

#include "version.h"
#include "globalVariable.h"
#include "network.h"

class VersionController
{
public:
    VersionController(QString pathToFolderWithAllVersions, Network *g_net);
    QList <Version*> getFullListVersion();
    QStringList* getFullListVersionStrList();
    QList <Version*> getListInsallVersion();
    QList <Version*> getListVersionOnServer();
    Version *getVersion(QString verName);
    bool deleteAllVersion();
    bool updateVersionsList();
    bool downloadVersion(Version ver);

private:
    QList <Version*> *versionsList;
    QFileInfo *folderWithAllVersions;
    Network *net;

    bool initVersionController (QString pathToFolder);
    bool initFolderWithAllVersions(QString pathToFolder);
    bool initVersionsList();
    bool fillingVersionList();
    QList<Version *> sortVersionList();
};

#endif // VERSIONCONTROLLER_H
