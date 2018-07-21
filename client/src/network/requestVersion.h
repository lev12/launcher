#ifndef REQUESTVERSION_H
#define REQUESTVERSION_H

#include "abstractRequest.h"
#include "requestCheckVersion.h"
#include "requestVersionInfo.h"
#include "requestFileListVersion.h"
#include "requestFile.h"
#include "config.h"
#include "globalVariable.h"

class RequestVersion : public AbstractRequest
{
public:
    RequestVersion(QString &serverAddress, unsigned short &serverPort, QString &Token , QString &app, QString &ver, QDir &saveFolder);
    virtual bool parse (QByteArray data);
private:
    bool init (QString versionName, QString applicationName, QDir saveFolder);

    bool getCheckVersion (QString *VerName, QString *AppName);
    bool getVersionInfo (QString *VerName, QString *AppName);
    bool getFileListVersion (QString *VerName, QString *AppName);
    bool getFile ();

    QUrl absoluteUrlPath (QString reletiveFilePath);
    QString absoluteFilePath (QString reletiveFilePath);

    QString *verName;
    QString *appName;
    int *indexDownloadFile;
    QStringList  *verFileReletivePathList;
    QString *token;
    QDir *saveFolder;
private slots:
    void receiveCheckVersion (QList<NetworkData> *response);
    void receiveVersionInfo (QList<NetworkData> *response);
    void receiveFileListVersion (QList<NetworkData> *response);
    void receiveFinishFileDownload (QList<NetworkData> *response);
};

#endif // REQUESTVERSION_H
