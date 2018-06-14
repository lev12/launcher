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
#include <QTcpSocket>

#include "globalVariable.h"
#include "log.h"
#include "config.h"

#include "requestActualVersion.h"
#include "requestAppicationInfo.h"
#include "requestApplicationList.h"
#include "requestCheckApplication.h"
#include "requestCheckVersion.h"
#include "requestFile.h"
#include "requestFileListVersion.h"
#include "requestVersion.h"
#include "requestVersionInfo.h"
#include "requestVersionsList.h"

class Network : public QObject
{
    Q_OBJECT
public:
    Network(Log *plog = NULL);

    bool isConnected ();

    ~Network();

    //verName type_num
    //appName all space _
    AbstractRequest* getActualVersion     (QString appName);
    AbstractRequest* getVersionList       (QString appName);
    //AbstractRequest* getSizeVersion       (QString appName, QString verName);
    AbstractRequest* getFileList          (QString appName, QString verName);
    AbstractRequest* getCheckVersion      (QString appName, QString verName);
    AbstractRequest* getVersion (QString appName, QString verName);
    AbstractRequest* getFile       (QUrl url, QFileInfo file);
    //AbstractRequest* getFileSize          (QString appName, QString verName, QString file);
    AbstractRequest* getVerInfo           (QString appName, QString verName);
    AbstractRequest* getAppInfo           (QString appName);
private:
    Log *log;
    QNetworkConfigurationManager *netConfig;
    bool *isConnect;
    unsigned short *portServer;
    QString *addressServer;
    QString *token;

    bool initConnect ();

    bool pingServer (QString adderss, qint16 port);

private slots:
    void setConnectState (bool state);
};

#endif // NETWORK_H
