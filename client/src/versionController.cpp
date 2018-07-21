#include "versionController.h"

VersionController::VersionController(QDir &pathToFolderWithAllVersions, Network &network, QString &AppName)
{
    if (AppName != QString("") || !pathToFolderWithAllVersions.exists())
    {
        //TODO thorw
        destroyed();
    }
    initAppName (&AppName);
    net = &network;

    //initVersionController(pathToFolderWithAllVersions);
    fillingVersionList();
    actualVersion = getListInsallVersion().at(0);
}

bool VersionController::initVersionController(QString &pathToFolder)
{
    folderWithAllVersions = NULL;
    versionsList = NULL;
    actualVersion = NULL;
    lastCurrentVersion = NULL;

    initFolderWithAllVersions(pathToFolder);
    initVersionsList();
    initActualVersion();

    return true;
}

bool VersionController::initFolderWithAllVersions(QString pathToFolder)
{
    if (folderWithAllVersions == NULL)
    {
        folderWithAllVersions = new QFileInfo (pathToFolder);
        return true;
    }
    return false;
}

bool VersionController::initVersionsList()
{
    if (versionsList == NULL)
    {
        versionsList = new QList <AbstractVersion*> ();
    }
    return true;
}

bool VersionController::initActualVersion()
{
    if (actualVersion == NULL)
    {
        actualVersion = new AbstractVersion ();
    }
    return true;
}

bool VersionController::initLastCurrentVersion()
{
    /*if (lastCurrentVersion == NULL)
    {
        lastCurrentVersion = new VersionInstall;
    }
    return true;*/
}

bool VersionController::fillingActualVersion()
{
    if (net == NULL) return false;
    AbstractRequest *dl = net->getActualVersion(*appName);
    QObject::connect(dl, AbstractRequest::replyServer, this, VersionController::setActualVersionNet);
    return true;
}

void VersionController::setActualVersionNet(QList<NetworkData> *response)
{
    if (response->length() == 0) return;

    actualVersion = getVersion(response->at(0).value.toString());
}

QList<AbstractVersion *> VersionController::getFullListVersion()
{
    return *versionsList;
}

QStringList* VersionController::getFullListVersionStrList()
{
    QStringList* resaultList = new QStringList();

    foreach (AbstractVersion *tempResList, *versionsList)
    {
        resaultList->operator <<(tempResList->getFullName());
    }

    return resaultList;
}

QList<VersionInstall *> VersionController::getListInsallVersion()
{
    QList <VersionInstall*> result;

    foreach (AbstractVersion *tempVer, *versionsList)
    {
        if (tempVer->getIsInstall())
        {
            result.operator <<(static_cast<VersionInstall*>(tempVer));
        }
    }

    return result;
}

QList<VersionNoInstall *> VersionController::getListVersionOnServer()
{
    QList <VersionNoInstall*> result;

    foreach (AbstractVersion *tempVer, *versionsList)
    {
        if (!tempVer->getIsInstall())
        {
            result.operator <<(static_cast<VersionNoInstall*>(tempVer));
        }
    }

    return result;
}

AbstractVersion* VersionController::getVersion(QString verName)
{
    foreach (AbstractVersion *tempVer, *versionsList)
    {
        if (tempVer->getFullName() == verName)
        {
            return tempVer;
        }
    }
    return NULL;
}

AbstractVersion *VersionController::getActualVersion()
{
    return actualVersion;
}

QString VersionController::getActualVersionStr()
{
    return actualVersion->getFullName();
}

VersionInstall *VersionController::getLsatCurrentVersion()
{
    if (lastCurrentVersion == NULL)
    {
        return NULL;
    }
    return lastCurrentVersion;
}

void VersionController::setLastCurrentVesion(QString verName)
{
    lastCurrentVersion = static_cast<VersionInstall*>(getVersion(verName));
}

bool VersionController::deleteAllVersion()
{
    foreach (AbstractVersion *tempVer, *versionsList)
    {
        static_cast<VersionInstall*>(tempVer)->deleteAllFile();
    }

    return true;
}

bool VersionController::updateVersionsList()
{
    fillingVersionList();
    return true;
}

bool VersionController::downloadVersion(VersionNoInstall ver)
{
    //net->getVersion("Electrical_Simulator", ver.getFullName());
    return false;
}

bool VersionController::initAppName(QString *name)
{
    appName = name;
    return true;
}

bool VersionController::fillingVersionList()
{
    QDir verFolder (folderWithAllVersions->absoluteFilePath());
    QStringList lstDirs = verFolder.entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    foreach (QString entry, lstDirs)
    {
        QString entryAbsPath = verFolder.absolutePath() + "/" + entry;
        if (VersionInstall::checkVersion(QFileInfo (entryAbsPath)))
        {
            VersionInstall *vertemp = new VersionInstall (*appName,entryAbsPath,net);
            versionsList->operator <<(vertemp);
        }
    }
    return false;
}

QList<AbstractVersion *> VersionController::sortVersionList()
{
    QList <AbstractVersion*> returnVersionsList;

    QList <AbstractVersion*> versions = *versionsList;
    QList <AbstractVersion*> preAlpha;
    QList <AbstractVersion*> Alpha;
    QList <AbstractVersion*> Beta;
    QList <AbstractVersion*> Release;

    for (int i(0); i < versions.length(); i++)
    {
        AbstractVersion *temp = versions.at(i);
        QString tempStrName = temp->getFullName();
        QString type = tempStrName.split(" ").at(0);

        if      (type == "pre_alpha")   preAlpha.operator <<(versions.at(i));
        else if (type == "alpha")       Alpha.operator <<(versions.at(i));
        else if (type == "beta")        Beta.operator <<(versions.at(i));
        else if (type == "release")     Release.operator <<(versions.at(i));
        else
        {
            qDebug () << "error sort versions";
        }
    }

    returnVersionsList.operator <<(Release);
    returnVersionsList.operator <<(Beta);
    returnVersionsList.operator <<(Alpha);
    returnVersionsList.operator <<(preAlpha);

    return returnVersionsList;
}

bool VersionController::isFoundVersions()
{
    if (versionsList->length() > 0){
        return true;
    }
    else{
        return false;
    }
}
