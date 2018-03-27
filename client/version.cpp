#include "version.h"

Version::Version()
{
    verNumber = NULL;
    verType = NULL;
    verIsInstall = NULL;
    verStartedFile = NULL;
    verFolder = NULL;
    verConfig = NULL;
    verFileList = NULL;
}

Version::~Version()
{
    delete verFolder;
    delete verConfig;
    delete verFileList;
}

bool Version::initInstallVersion(QString pathToFolderWithVesrions)
{
    initVerIsInstall(true);
    initVerFolder(pathToFolderWithVesrions);
    initConfig(pathToFolderWithVesrions);
    fillingFileList();
    fillingOfConfig();
}

bool Version::initNoIntallVersion(QString verName)
{
    initVerIsInstall(false);
    initVerNumberAndType(verName);
}

bool Version::initVerIsInstall(bool VerIsInstall)
{
    verIsInstall = &VerIsInstall;
    return true;
}

bool Version::initVerFolder(QString pathToFolderWithVesrions)
{
    if (!(QFileInfo(pathToFolderWithVesrions).isDir()))
    {
        return false;
    }

    verFolder = new QDir(pathToFolderWithVesrions);
    return true;
}

bool Version::initStartedFile(QString startFile)
{
    verStartedFile = new QFileInfo (startFile);
    return true;
}

bool Version::initConfig(QString pathToFolderWithVesrions)
{
    QString pathToConfig = pathToFolderWithVesrions;
    pathToConfig.append("/version_config.cfg");
    verConfig = new Config (pathToConfig);

    return true;
}

bool Version::initVerNumberAndType (QString verName)
{
    QStringList lstVersionName = verName.split(" ");

    *verNumber = lstVersionName.at(1).toInt();

    *verType = stringToVersionType(QString(lstVersionName.at(0)));
    return true;
}

QString Version::getFullName()
{
    QString name;
    QString type = versionTypeToString(*verType);
    QString number = QString::number(*verNumber);

    if (type != "null")
    {
        name.append(type);
        name.append(" ");
    }
    name.append(number);

    return name;
}

QString Version::getFullPath()
{
    if (verFolder == NULL)
    {
        return "no init version folder";
    }

    QString path = verFolder->absolutePath();
    return path;
}

int Version::getVersionNumber()
{
    return *verNumber;
}

VersionType Version::getVersionType()
{
    return *verType;
}

bool Version::getIsInstall()
{
    return verIsInstall;
}

int Version::getVersionSize()
{
    int verSize;
    QList <QFileInfo> tempVerFileList = *verFileList;

    foreach (QFileInfo tempFile, tempVerFileList)
    {
        verSize = verSize + tempFile.size();
    }

    return verSize;
}

QList <QFileInfo> *Version::getFileList()
{
    return verFileList;
}

QString Version::getPathStartedFile()
{
    return verStartedFile->absoluteFilePath();
}

QString Version::getStartedFile()
{
    return verStartedFile->fileName();
}

bool Version::verDeleteFile()
{
    if (verFolder == NULL)
    {
        return false;
    }

    removeFolder(*verFolder);
    return true;
}

bool Version::fillingFileList()
{
    if (verFileList == NULL)
    {
        return false;
    }
    verFileList = new QList <QFileInfo>;
    fillingFileListOfDir(*verFolder);

    return true;
}

bool Version::fillingFileListOfDir(QDir &dir)
{
    QStringList lstDirs = dir.entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    QStringList lstFiles = dir.entryList(QDir::Files);


    foreach (QString tempFileStr, lstFiles)
    {
        QString tempFilePath = dir.absolutePath() + "/" + tempFileStr;
        QFileInfo tempFileInfo = QFileInfo(tempFilePath);
        verFileList->operator <<(tempFileInfo);
    }

    foreach (QString tempDirStr, lstDirs)
    {
        QString tempDirPath = dir.absolutePath() + "/" + tempDirStr;
        QDir tempDir = QDir (tempDirPath);
        fillingFileListOfDir(tempDir);
    }
    return true;
}

bool Version::fillingConfig()
{
    verConfig->set("Version_Type", versionTypeToString(*verType));
    verConfig->set("Version_Number", QString::number(*verNumber));
    verConfig->set("Start_File", verStartedFile->filePath());
    return true;
}

bool Version::fillingOfConfig()
{
    if (verConfig == NULL)
    {
        return false;
    }

    verNumber = new int;
    *verNumber = (verConfig->get("Version_Number").at(0).toInt());
    VersionType verTypeTemp = stringToVersionType(verConfig->get("Version_Type").at(0));
    verType = &verTypeTemp;
    QFileInfo verStartedFileTemp (verConfig->get("Start_File").at(0));
    verStartedFile = &verStartedFileTemp;
}

int Version::removeFolder(QDir &dir)
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

QString Version::versionTypeToString (VersionType type)
{
    QString type_str;
    switch (type) {
    case pre_alpha:
        type_str = "pre-alpha";
        break;
    case alpha:
        type_str = "alpha";
        break;
    case beta:
        type_str = "beta";
        break;
    case release:
        type_str = "release";
        break;
    case null:
        type_str = "null";
        break;
    default:
        type_str = "error";
        break;
    }
    return type_str;
}

VersionType Version::stringToVersionType (QString str)
{
    VersionType type;
    if (str == "pre-alpha")
    {
        type = pre_alpha;
    }
    else if (str == "alpha")
    {
        type = alpha;
    }
    else if (str == "beta")
    {
        type = beta;
    }
    else if (str == "release")
    {
        type = release;
    }
    else
    {
        type = null;
    }

    return type;
}

bool Version::checkVersion(QFileInfo path)
{
    if (path.isFile())
    {
        return false;
    }

    QString pathToConfigVersion = path.absoluteFilePath();
    pathToConfigVersion.append("/data version.ini");
    QFile confIni (pathToConfigVersion);
    if (!(confIni.open(QFile::ReadOnly | QFile::Text)))
    {
        return false;
    }

    QStringList data;
    Config cfg (pathToConfigVersion);
    data.operator <<(cfg.get("Version_Type"));
    data.operator <<(cfg.get("Version_Number"));
    data.operator <<(cfg.get("Start_File"));

    if (data.at(0) == "pre-alpha"
     || data.at(0) == "alpha"
     || data.at(0) == "beta"
     || data.at(0) == "release")
    {
        if (QString(data.at(1)).toInt() != 0)
        {
            QString pathToExe = path.absoluteFilePath();
            pathToExe.append("/");
            pathToExe.append(data.at(2));
            QFile exe (pathToExe);
            if (exe.exists())
            {
                return true;
            }
        }
    }

    return false;
}

