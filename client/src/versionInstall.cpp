#include "versionInstall.h"

VersionInstall::VersionInstall(QString AppName, QString pathToFolderWithVersions, Network *network) : AbstractVersion ()
{
    initIsInatall(true);
    initAppName(AppName);
    initNetwork(network);
    initRootFolder(pathToFolderWithVersions);
    initVerName(verFolder->dirName());
    verFileList = new QList <QFileInfo*>;
    fillingFileList (verFolder);

    if (initConfig(verFolder->absolutePath()))
    {
        initStartedFile (verConfig,verFolder);
        initSize (verFileList);
    }
    else
    {
        if (!net->isConnected())
        {
            throw std::logic_error(getExceptionVersion(QString("not found config file and no connect network")));
        }
        requestConfigFromNetwork (net);
    }
}

VersionInstall::~VersionInstall()
{

}

QString VersionInstall::getStartedFileName()
{
    if (!verStartedFile->exists())
    {
        if (net->isConnected())
        {
            //TODO
        }
        else
        {
            throw std::logic_error(getExceptionVersion(QString("not found started file")));
        }
    }

    return verStartedFile->fileName();
}

QString VersionInstall::getStartedFilePath()
{
    if (!verStartedFile->exists())
    {
        //TODO
    }

    return verStartedFile->absoluteFilePath();
}

quint64 &VersionInstall::getVersionSize()
{
    return *verSize;
}

QList<QFileInfo *> &VersionInstall::getFileList()
{
    return *verFileList;
}

bool VersionInstall::deleteAllFile()
{
    if (!verFolder->exists())
    {
        //TODO throw
        throw std::logic_error ("");
        return false;
    }
    removeFolder(*verFolder);
    delete verFileList;
    verFileList = new QList <QFileInfo*> ();
    verFolder = new QDir ();
    destroyed ();
    return true;
}

int VersionInstall::removeFolder(QDir &dir)
{
    int res = 0;
    QStringList lstDirs = dir.entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    QStringList lstFiles = dir.entryList(QDir::Files);

    foreach (QString entry, lstFiles)
    {
     QString entryAbsPath = dir.absolutePath() + "/" + entry;
     QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
     QFile::remove(entryAbsPath);
    }

    foreach (QString entry, lstDirs)
    {
     QString entryAbsPath = dir.absolutePath() + "/" + entry;
     QDir dr(entryAbsPath);
     removeFolder(dr);
    }

    if (!QDir().rmdir(dir.absolutePath()))
    {
      res = 1;
    }
    return res;
}

bool VersionInstall::requestConfigFromNetwork(Network *network)
{
    if (!network->isConnected())
    {
        return false;
    }
    AbstractRequest *request = network->getVersionInfo(*appName,getFullName());
    connect(request, AbstractRequest::replyServer, this, reciveConfig);
    return true;
}

std::string VersionInstall::getExceptionVersion(const QString &str)
{
    QString estr (*appName);
    estr.append(" ");
    estr.append(getFullName());
    estr.append(" ");
    estr.append(str);
    return estr.toStdString();
}

void VersionInstall::reciveConfig(QList<NetworkData> *response)
{
    verConfig->clear();
    foreach (NetworkData netData, *response)
    {
        verConfig->set(netData.key,netData.value.toString());
    }
    verConfig->save();
}

bool VersionInstall::checkVersion(QFileInfo path)
{
    if (path.isFile())
    {
        return false;
    }

    QString pathToConfigVersion = path.absoluteFilePath();
    pathToConfigVersion.append("/version_config.cfg");
    QFile confIni (pathToConfigVersion);
    if (!(confIni.open(QFile::ReadOnly | QFile::Text)))
    {
        return false;
    }
    return true;
}

bool VersionInstall::initConfig(QString pathToFolderWithVesrions)
{
    QString pathToConfig = pathToFolderWithVesrions;
    pathToConfig.append("/version_config.cfg");
    if (!(QFile::exists(pathToConfig)))
    {
        return false;
    }
    verConfig = new Config (pathToConfig);

    return true;
}

bool VersionInstall::initRootFolder(QString pathToFolderWithVesrions)
{
    if (!(QFileInfo(pathToFolderWithVesrions).isDir()))
    {
        //TODO thorw
        return false;
    }

    verFolder = new QDir(pathToFolderWithVesrions);
    return true;
}

bool VersionInstall::initNetwork(Network *network)
{
    if (network == NULL) return false;
    net = network;
    return true;
}

bool VersionInstall::fillingFileList(QDir *folder)
{
    QStringList lstDirs = folder->entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    QStringList lstFiles = folder->entryList(QDir::Files);


    foreach (QString tempFileStr, lstFiles)
    {
        QString tempFilePath = folder->absolutePath() + "/" + tempFileStr;
        QFileInfo* tempFileInfo = new QFileInfo (tempFilePath);
        verFileList->operator <<(tempFileInfo);
    }

    foreach (QString tempDirStr, lstDirs)
    {
        QString tempDirPath = folder->absolutePath() + "/" + tempDirStr;
        QDir tempDir (tempDirPath);
        fillingFileList(&tempDir);
    }
    return true;
}

/*bool VersionInstall::initVerName(Config *verCfg)
{
    verType = new VersionType;
    *verType = stringToVersionType (verCfg->get("Version_Type").at(0));

    verNumber = new int;
    *verNumber = verCfg->get("Version_Number").at(0).toInt();

    return true;
}*/

bool VersionInstall::initStartedFile(Config *verCfg, QDir *rootFolder)
{
    if (!rootFolder->exists())
    {
        //TODO throw
        return false;
    }
    QString startFileName = verCfg->get("Start_File").at(0);
    if (startFileName == verCfg->errorResponse)
    {
        //TODO throw
        return false;
    }
    QString pathToStartFile = rootFolder->absolutePath() + "/" + startFileName;
    verStartedFile = new QFileInfo (pathToStartFile);
    return true;
}

bool VersionInstall::initSize(QList<QFileInfo *> *files)
{
    verSize = new quint64;
    *verSize = 0;
    foreach (QFileInfo *tempFile, *files)
    {
        *verSize += tempFile->size();
    }
    return true;
}
