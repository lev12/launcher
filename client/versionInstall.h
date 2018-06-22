#ifndef VERSIONINSTALL_H
#define VERSIONINSTALL_H

#include "abstractVersion.h"

class VersionInstall : public AbstractVersion
{
public:
    VersionInstall(QString AppName, Network *network, QString pathToFolderWithVersions);
    ~VersionInstall ();

    QString getStartedFileName();
    QString getStartedFilePath();
    qint64 *getVersionSize();
    QList<QFileInfo*> *getFileList();

    bool deleteAllFile();
    static bool checkVersion (QFileInfo path);
private:
    Network *net;

    QFileInfo *verStartedFile;
    QDir *verFolder;
    Config *verConfig;
    QList <QFileInfo*> *verFileList;
    qint64 *verSize;

    //no read from config
    bool initConfig(QString pathToFolderWithVesrions);
    bool initRootFolder(QString pathToFolderWithVesrions);
    bool initNetwork (Network *network);
    bool fillingFileList (QDir *folder);

    //read from config
    bool initStartedFile (Config *verCfg, QDir *rootFolder);
    bool initSize (QList <QFileInfo*> *files);

    int removeFolder(QDir &dir);

    //filling config
    bool requestConfigFromNetwork (Network *network);

private slots:
    void reciveConfig (QList<NetworkData> *response);
};

#endif // VERSIONINSTALL_H
