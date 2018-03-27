#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStorageInfo>
#include <QDir>
#include <QList>
#include <QTimer>
#include <QThread>
#include <QMap>

#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkConfigurationManager>

#include "globalVariable.h"
#include "log.h"
#include "config.h"
#include "version.h"
#include "downloader.h"
#include "downloaderForFile.h"
#include "downloaderForVersion.h"

class Network : public QObject
{
    Q_OBJECT
public:
    Network(Log *plog);

    bool isConnected ();

    ~Network();

    //verName type_num
    //appName all space _
    Downloader* getActualVersion     (QString appName);
    Downloader* getVersionList       (QString appName);
    Downloader* getExeFile           (QString appName, QString verName);
    Downloader* getSizeVersion       (QString appName, QString verName);
    Downloader* getFileList          (QString appName, QString verName);
    Downloader* getCheckVersion      (QString appName, QString verName);
    DownloaderForVersion* getVersion (QString appName, QString verName);
    DownloaderForFile* getFile       (QUrl url, QFileInfo file);
    Downloader* getFileSize          (QString appName, QString verName, QString file);


private:
    Config *cfg;
    Log *log;
    QNetworkConfigurationManager *netConfig;
    bool *isConnect;

private slots:
    void setConnectState (bool state);
};

#endif // NETWORK_H
