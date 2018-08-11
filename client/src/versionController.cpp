#include "versionController.h"

VersionController::VersionController(QDir &pathToFolderWithAllVersions, Network &network, QString &AppName) :
    net (&network), folderWithAllVersions (&pathToFolderWithAllVersions), appName (&AppName)
{
    if (AppName != QString(""))
    {
        QString estr ("no valid application name: ");
        estr.append(AppName);
        throw std::invalid_argument (estr.toStdString());
    }
    if(!pathToFolderWithAllVersions.exists())
    {
        QString estr ("no exists folder: ");
        estr.append(AppName);
        throw std::invalid_argument (estr.toStdString());
    }
    net = &network;

    //initVersionController(pathToFolderWithAllVersions);
    fillingVersionList(*folderWithAllVersions);
}

bool VersionController::initVersionController(QString &pathToFolder)
{
    initVersionsList();

    return true;
}

bool VersionController::initVersionsList()
{
    if (versionsList == NULL)
    {
        versionsList = new QList <AbstractVersion*> ();
    }
    return true;
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
            result << static_cast<VersionNoInstall*>(tempVer);
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
    return fillingVersionList(*folderWithAllVersions);
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

bool VersionController::fillingVersionList(const QDir &verFolder)
{
    if (!verFolder.exists())
    {
        return false;
    }
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
    return true;
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
