#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QByteArray>
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
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkConfigurationManager>
#include <QTcpSocket>

#include "globalVariable.h"
#include "log.h"

#include "requestActualVersion.h"
#include "requestApplicationInfo.h"
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
    Network(QString AddressServer, quint16 PortServer, Log *plog = NULL);

    virtual bool isConnected ();

    ~Network();

    //verName type_num
    //appName all space _
    virtual AbstractRequest *getActualVersion(QString appName);
    virtual AbstractRequest *getVersionList(QString appName);
    virtual AbstractRequest *getApplicationList();
    //AbstractRequest* getSizeVersion       (QString appName, QString verName);
    virtual AbstractRequest *getFileListVersion(QString appName, QString verName);
    virtual AbstractRequest *getCheckVersion(QString appName, QString verName);
    virtual AbstractRequest* getVersion (QString &appName, QString &verName, QDir &saveFolderPath);
    virtual AbstractRequest *getFile(QUrl url, QFileInfo file);
    //AbstractRequest* getFileSize          (QString appName, QString verName, QString file);
    virtual AbstractRequest *getVersionInfo(QString appName, QString verName);
    virtual AbstractRequest *getAppInfo(QString appName);

    static bool pingServer (QString adderss, qint16 port);
private:
    Log *log;
    QNetworkConfigurationManager *netConfig;
    bool *isConnect;

    bool initConnect ();

private slots:
    void setConnectState (bool state);

protected:
    unsigned short *portServer;
    QString *addressServer;
    QString *token;

};

#endif // NETWORK_H
