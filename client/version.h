#ifndef VERSION_H
#define VERSION_H

#include <QList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QObject>

#include "globalVariable.h"
#include "config.h"
#include "network/network.h"


class Version : public QObject
{
    Q_OBJECT
public:
    //verName =  typeVersion space versionNumber


    Version(QString AppName, Network *network);

    ~Version();
    QString getFullName();
    QString getFullPath();
    int getVersionNumber();
    VersionType getVersionType();
    bool getIsInstall();
    QString getStartedFile();
    QString getPathStartedFile();
    int getVersionSize();
    QList<QFileInfo> *getFileList();
    QStringList getSupportLanguage();
    QList <Platform> getSupportPlatform ();
    QString getRecommendedSystemRequirements ();
    QString getMinimumSystemRequirements ();

    bool verDeleteFile();

    bool initInstallVersion(QString pathToFolderWithVesrions);
    bool initNoIntallVersion(QString verName);
    bool installVersion();

    static bool checkVersion (QFileInfo path);

private:
    QString *appName;
    int *verNumber;
    VersionType *verType;
    bool *verIsInstall;
    QFileInfo *verStartedFile;
    QDir *verFolder;
    Config *verConfig;
    QList <QFileInfo> *verFileList;
    Network *net;

    QList <Platform> *verSupportPlatform;
    QStringList *verSupportLanguge;
    QString *verRecSysReq;
    QString *verMinSysReq;

    //and for no install version
    bool initAppName (QString AppName);
    bool initVerNumberAndTypeInNoInstall(QString verName);

    //no read from config
    bool initConfig(QString pathToFolderWithVesrions);
    bool initVerFolder(QString pathToFolderWithVesrions);
    void initVerIsInstall(bool VerIsInstall);
    bool initNetwork (Network *network);

    //read from config
    bool initVerName ();
    bool initStartedFile ();
    bool initVerSupportPlatform ();
    bool initVerSupportLanguge ();
    bool initVerRecSysReq ();
    bool initVerMinSysReq ();

    bool requestInfoVer ();

    bool fillingFileList();
    bool fillingFileListOfDir(QDir &dir);
    bool fillingConfig();
    bool fillingOfConfig(); // fill verNumber,verType,verStartedFile of config

    int removeFolder (QDir &dir);
    static QString versionTypeToString (VersionType type);
    static VersionType stringToVersionType (QString str);
    static QList<Platform> strToPlatform (QStringList platformStrList);

private slots:
    void responseInfoVerAndFillingConfig (QStringList *response);
};

#endif // VERSION_H
