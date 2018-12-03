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
#include "versionControllerException.h"
#include "network/network.h"

class VersionController : public QObject
{
    Q_OBJECT
public:
    VersionController(QDir &pathToFolderWithAllVersions, Network &network, QString &AppName);
    QList <AbstractVersion*> getListVersion();
    QStringList getListVersionStrList();
    QList <VersionInstall*> getListInsallVersion();
    QList<VersionNoInstall*> getListNoInstallVersion();
    AbstractVersion *getVersion(QString verName);

    bool deleteAllVersion();
    bool updateVersionsList();
    bool downloadVersion(VersionNoInstall ver);

    bool isFoundVersions ();
    static QList<AbstractVersion *> sortVersionList(const QList<AbstractVersion *> &versions);
private:
    QList <AbstractVersion*> *versionList;
    QDir *folderWithAllVersions;
    Network *net;
    QString *appName;

    QList<AbstractVersion *> getVersionList(const QDir &verFolder);

signals:
    void responseActualVersion (QString verName);
    void downloadNewVersion (VersionInstall *VersionInst);

private slots:
    void reciveDownloadVersion (QList<NetworkData> *response);
};

#endif // VERSIONCONTROLLER_H
