#include "version.h"

Version::Version(QString AppName, Network *network)
{
    verNumber = NULL;
    verType = NULL;
    verIsInstall = NULL;
    verStartedFile = NULL;
    verFolder = NULL;
    verConfig = NULL;
    verFileList = NULL;
    verSupportPlatform = NULL;
    verSupportLanguge = NULL;
    verRecSysReq = NULL;
    verMinSysReq = NULL;
    net = NULL;

    initAppName (AppName);
    initNetwork(network);
}

Version::~Version()
{
    delete verFolder;
    delete verConfig;
    delete verFileList;
}

//inti version
bool Version::initInstallVersion(QString pathToFolderWithVesrions)
{
    if (!(checkVersion(QFileInfo(pathToFolderWithVesrions))))
    {
        return false;
    }

    initVerIsInstall(true);
    initVerFolder(pathToFolderWithVesrions);
    initConfig(pathToFolderWithVesrions);
    initVerNumberAndTypeInNoInstall(verFolder->dirName());

    fillingFileList();
    if (verConfig->isEmpty())
    {
        requestInfoVer ();
    }
    else
    {
        initVerName ();
        initStartedFile ();
        initVerSupportPlatform ();
        initVerSupportLanguge ();
        initVerRecSysReq ();
        initVerMinSysReq ();
    }
    return true;
}

bool Version::initNoIntallVersion(QString verName)
{
    initVerIsInstall(false);
    initVerNumberAndTypeInNoInstall(verName);
    return true;
}

bool Version::installVersion()
{
    return true;
}

//init var
bool Version::initAppName(QString AppName)
{
    appName = new QString();
    *appName = AppName;
    return true;
}

bool Version::initVerNumberAndTypeInNoInstall (QString verName)
{
    QStringList lstVersionName = verName.split(" ");
    if (lstVersionName.length() < 2)
    {
        return false;
    }

    bool isConvertToInt;
    verNumber = new int;
    *verNumber = lstVersionName.at(1).toInt(&isConvertToInt);
    if (!isConvertToInt)
    {
        return false;
    }
    verType = new VersionType;
    *verType = stringToVersionType(QString(lstVersionName.at(0)));
    return true;
}

void Version::initVerIsInstall(bool VerIsInstall)
{
    verIsInstall = new bool;
    *verIsInstall = VerIsInstall;
}

bool Version::initVerFolder(QString pathToFolderWithVesrions)
{
    if (!(QFileInfo(pathToFolderWithVesrions).isDir()))
    {
        //TODO
        return false;
    }

    verFolder = new QDir(pathToFolderWithVesrions);
    return true;
}

bool Version::initConfig(QString pathToFolderWithVesrions)
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

bool Version::initNetwork(Network *network)
{
    if (network == NULL) return false;
    net = network;
    return true;
}

//init read from config
bool Version::initVerName()
{
    verType = new VersionType;
    *verType = stringToVersionType (verConfig->get("Version_Type").at(0));

    verNumber = new int;
    *verNumber = verConfig->get("Version_Number").at(0).toInt();

    return true;
}

bool Version::initStartedFile()
{
    QString pathToStartFile = verFolder->absolutePath();
    pathToStartFile.append("/");
    pathToStartFile.append(verConfig->get("Start_File").at(0));

    verStartedFile = new QFileInfo (pathToStartFile);
    return true;
}

bool Version::initVerSupportPlatform()
{
    if (verConfig == NULL) return false;

    QStringList platform = verConfig->get("Platform");
    if (platform.at(0) == "false")
    {
        return false;
    }

    *verSupportPlatform = strToPlatform(platform);

    return true;
}

bool Version::initVerSupportLanguge()
{
    if (verConfig == NULL) return false;

    return true;
}

bool Version::initVerRecSysReq()
{
    if (verConfig == NULL) return false;

    return true;
}

bool Version::initVerMinSysReq()
{
    if (verConfig == NULL) return false;

    return true;
}

//request on server

bool Version::requestInfoVer()
{
    if (net == NULL) return false;

    QString verName = versionTypeToString (*verType);
    verName.append("_");
    verName.append(*verNumber);
    Downloader *dl = net->getVerInfo(*appName, verName);
    QObject::connect(dl, Downloader::replyServer, this, Version::responseInfoVerAndFillingConfig);

    return true;
}

void Version::responseInfoVerAndFillingConfig(QStringList *response)
{
    if (response->length() == 0) return;

    qDebug () << response;

    QStringList listKey;
    QStringList listValue;

    for (int i (0); i < response->length(); i++)
    {
        if (i%2 == 0)
        {
            listKey.operator <<(response->at(i));
        }
        else
        {
            listValue.operator <<(response->at(i));
        }
    }

    for (int i(0); i < listKey.length();i++)
    {
        verConfig->set(listKey.at(i),listValue.at(i));
    }
    verConfig->save();

    return;
}


//get
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

QStringList Version::getSupportLanguage()
{
    if (verSupportLanguge == NULL) initVerSupportLanguge ();
    return *verSupportLanguge;
}

QList<Platform> Version::getSupportPlatform()
{
    if (verSupportPlatform == NULL) initVerSupportPlatform ();
    return *verSupportPlatform;
}

QString Version::getRecommendedSystemRequirements()
{
    if (verRecSysReq == NULL) initVerRecSysReq ();
    return *verRecSysReq;
}

QString Version::getMinimumSystemRequirements()
{
    if (verMinSysReq == NULL) initVerMinSysReq ();
    return *verMinSysReq;
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
    return true;
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

bool Version::checkVersion(QFileInfo path)
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

    /*QStringList data;
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

    return false;*/
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

QList<Platform> Version::strToPlatform (QStringList platformStrList)
{
    QList<Platform> resault;
    foreach (QString tempList, platformStrList)
    {
        if (tempList == "PC") resault << PC;
        else if (tempList == "MAC") resault << MAC;
        else if (tempList == "Android") resault << Android;
        else if (tempList == "IOS") resault << IOS;
        else if (tempList == "XBox") resault << XBox;
        else if (tempList == "PlayStation") resault << PlayStation;
    }
    return resault;
}
