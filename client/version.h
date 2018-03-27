#ifndef VERSION_H
#define VERSION_H

#include <QList>
#include <QString>
#include <QDir>
#include <QFile>

#include "globalVariable.h"
#include "config.h"


class Version
{
public:
    //verName =  typeVersion space versionNumber


    Version();

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
    bool verDeleteFile();

    bool initInstallVersion(QString pathToFolderWithVesrions);
    bool initNoIntallVersion(QString verName);
    bool installVersion(QString pathToFolderWithVesrions, QString verName, QString startedFileName);

    static bool checkVersion (QFileInfo path);

private:
    int *verNumber;
    VersionType *verType;
    bool *verIsInstall;
    QFileInfo *verStartedFile;
    QDir *verFolder;
    Config *verConfig;
    QList <QFileInfo> *verFileList;

    bool initStartedFile(QString startFile);
    bool initConfig(QString pathToFolderWithVesrions);
    bool initVerFolder(QString pathToFolderWithVesrions);
    bool initVerIsInstall(bool VerIsInstall);
    bool initVerNumberAndType(QString verName);

    bool fillingFileList();
    bool fillingFileListOfDir(QDir &dir);
    bool fillingConfig();
    bool fillingOfConfig(); // fill verNumber,verType,verStartedFile of config
    int removeFolder (QDir &dir);
    QString versionTypeToString (VersionType type);
    VersionType stringToVersionType (QString str);
};

#endif // VERSION_H
