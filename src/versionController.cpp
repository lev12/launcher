#include "versionController.h"

VersionController::VersionController(QDir &pathToFolderWithAllVersions, Network &network, QString &AppName) :
    net (&network), folderWithAllVersions (&pathToFolderWithAllVersions), appName (&AppName)
{
    if (AppName == QString(""))
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
    versionList = new QList <AbstractVersion*> ();
    *versionList = getVersionList(*folderWithAllVersions);
}

QList<AbstractVersion *> VersionController::getListVersion()
{
    return *versionList;
}

QStringList VersionController::getListVersionStrList()
{
    QStringList resaultList;

    foreach (AbstractVersion *tempResList, *versionList)
    {
        resaultList << tempResList->getFullName();
    }

    return resaultList;
}

QList<VersionInstall *> VersionController::getListInsallVersion()
{
    QList <VersionInstall*> result;

    foreach (AbstractVersion *tempVer, *versionList)
    {
        if (tempVer->getIsInstall())
        {
            result.operator <<(static_cast<VersionInstall*>(tempVer));
        }
    }

    return result;
}

QList<VersionNoInstall *> VersionController::getListNoInstallVersion()
{
    QList <VersionNoInstall*> result;

    foreach (AbstractVersion *tempVer, *versionList)
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
    foreach (AbstractVersion *tempVer, *versionList)
    {
        if (tempVer->getFullName() == verName)
        {
            return tempVer;
        }
    }
    throw VersionControllerException (1002,QString ("not found version:") + verName);
    return NULL;
}

bool VersionController::deleteAllVersion()
{
    foreach (AbstractVersion *tempVer, *versionList)
    {
        static_cast<VersionInstall*>(tempVer)->deleteAllFile();
    }

    return true;
}

bool VersionController::updateVersionsList()
{
    try
    {
        *versionList = getVersionList(*folderWithAllVersions);
    }
    catch (const std::invalid_argument &e)
    {
        qDebug () << e.what();
        if (!folderWithAllVersions->exists())
        {
            QString estr ("no exists folder with version");
            throw VersionControllerException (1001, estr);
        }
        return false;
    }
    return true;
}

bool VersionController::downloadVersion(VersionNoInstall ver)
{
    if (!net->isConnected())
    {
        return false;
    }
    QString *verName = new QString (ver.getFullName());
    AbstractRequest *requestVer = net->getVersion(*appName,*verName,*folderWithAllVersions);
    connect(requestVer,&RequestVersion::replyServer,this,&VersionController::reciveDownloadVersion);
    return true;
}

void VersionController::reciveDownloadVersion(QList<NetworkData> *response)
{
    QString folderVersion = response->at(0).value.toString();
    VersionInstall *newVer = new VersionInstall (*appName,folderVersion,net);
    updateVersionsList();
    downloadNewVersion (newVer);
}

QList <AbstractVersion*> VersionController::getVersionList(const QDir &verFolder)
{
    if (!verFolder.exists())
    {
        QString estr ("no exists folder: ");
        estr.append(verFolder.absolutePath());
        throw std::invalid_argument (estr.toStdString());
    }
    QList <AbstractVersion*> verList;
    qDebug () << verFolder;
    QStringList lstDirs = verFolder.entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    qDebug () << lstDirs;
    foreach (QString entry, lstDirs)
    {
        QString entryAbsPath = verFolder.absolutePath() + "/" + entry;
        if (VersionInstall::checkVersion(QFileInfo (entryAbsPath)))
        {
            VersionInstall *vertemp;
            try
            {
                vertemp = new VersionInstall (*appName,entryAbsPath,net);
            }
            catch (std::exception &e)
            {
                continue;
            }
            verList << vertemp;
        }
    }
    verList = sortVersionList(verList);
    return verList;
}

QList<AbstractVersion *> VersionController::sortVersionList(const QList<AbstractVersion *> &versions)
{
    QList <AbstractVersion*> returnVersionsList;

    QList <AbstractVersion*> preAlpha;
    QList <AbstractVersion*> Alpha;
    QList <AbstractVersion*> Beta;
    QList <AbstractVersion*> Release;

    for (int i(0); i < versions.length(); i++)
    {
        AbstractVersion *temp = versions.at(i);
        QString tempStrName = temp->getFullName();
        QString type = tempStrName.split(" ").at(0);

        if      (type == "pre-alpha")   preAlpha.operator <<(versions.at(i));
        else if (type == "alpha")       Alpha.operator <<(versions.at(i));
        else if (type == "beta")        Beta.operator <<(versions.at(i));
        else if (type == "release")     Release.operator <<(versions.at(i));
        else
        {
            qDebug () << type << "error sort versions";
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
    if (versionList->length() > 0){
        return true;
    }
    else{
        return false;
    }
}
