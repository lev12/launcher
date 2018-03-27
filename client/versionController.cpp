#include "versionController.h"

VersionController::VersionController(QString pathToFolderWithAllVersions, Network *g_net)
{
    initVersionController(pathToFolderWithAllVersions);
    net = g_net;
    fillingVersionList();
}

bool VersionController::initVersionController(QString pathToFolder)
{
    folderWithAllVersions = NULL;
    versionsList = NULL;

    initFolderWithAllVersions(pathToFolder);
    initVersionsList();

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
        versionsList = new QList <Version*> ();
    }
    return true;
}

QList <Version*> VersionController::getFullListVersion()
{
    return *versionsList;
}

QStringList* VersionController::getFullListVersionStrList()
{
    QStringList* resaultList = new QStringList();

    foreach (Version *tempResList, *versionsList)
    {
        resaultList->operator <<(tempResList->getFullName());
    }

    return resaultList;
}

QList <Version*> VersionController::getListInsallVersion()
{
    QList <Version*> result;

    foreach (Version *tempVer, *versionsList)
    {
        if (tempVer->getIsInstall())
        {
            result.operator <<(tempVer);
        }
    }

    return result;
}

QList <Version*> VersionController::getListVersionOnServer()
{
    QList <Version*> result;

    foreach (Version *tempVer, *versionsList)
    {
        if (!tempVer->getIsInstall())
        {
            result.operator <<(tempVer);
        }
    }

    return result;
}

Version* VersionController::getVersion(QString verName)
{
    foreach (Version *tempVer, *versionsList)
    {
        if (tempVer->getFullName() == verName)
        {
            return tempVer;
        }
    }
    return NULL;
}

bool VersionController::deleteAllVersion()
{
    foreach (Version *tempVer, *versionsList)
    {
        tempVer->verDeleteFile();
    }

    return true;
}

bool VersionController::updateVersionsList()
{
    fillingVersionList();
    return true;
}

bool VersionController::downloadVersion(Version ver)
{
    net->getVersion("Electrical_Simulator", ver.getFullName());
    return false;
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
        if (Version::checkVersion(QFileInfo (entryAbsPath)))
        {
            Version *vertemp = new Version ();
            vertemp->initInstallVersion(entryAbsPath);
            versionsList->operator <<(vertemp);
        }
    }
    return false;
}

QList <Version*> VersionController::sortVersionList()
{
    QList <Version*> returnVersionsList;

    QList <Version*> versions = *versionsList;
    QList <Version*> preAlpha;
    QList <Version*> Alpha;
    QList <Version*> Beta;
    QList <Version*> Release;

    for (int i(0); i < versions.length(); i++)
    {
        Version *temp = versions.at(i);
        QString tempStrName = temp->getFullName();
        QString type = tempStrName.split(" ").at(0);

        if      (type == "pre-alpha")   preAlpha.operator <<(versions.at(i));
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
