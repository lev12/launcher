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

#include "global_variable.h"
#include "log.h"
#include "config.h"

class Network : public QObject
{
    Q_OBJECT

private:
    QString _toSpace (QString str);
    QString spaceTo_ (QString str);
    QString deleteForRx (QString data);

    bool parse              (QByteArray data, QTcpSocket *server);
    bool parseListVersions  (QByteArray data);
    bool parseDownloadFile  (QByteArray data, QTcpSocket *server);
    bool parseUploadLog     (QByteArray data, QTcpSocket *server);
    bool parseAcualVersion  (QByteArray data);
    bool parseFileSize      (QByteArray data);

    bool download = false;
    int filesNum;
    QString downloadApp;
    QString downloadVersion;
    qint64 fileSize;
    QFile *createFile;
    QStringList files;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private slots:

    void readServer(QNetworkReply *reply);

public slots:

    bool sendLog                (QString path);


    //verName type_num
    //appName all space _
    bool getVersionList     (QString appName);
    bool getActualVersion   (QString appName);
    bool getExeFile         (QString appName, QString verName);
    bool getSizeVersion     (QString appName, QString verName);
    bool getFileList        (QString appName, QString verName);
    bool checkVersion       (QString appName, QString verName);
    bool getVersion         (QString appName, QString verName);
    bool getFile            (QString appName, QString verName, QString file);
    bool downloadFileRS     ();
    bool getFileSize        (QString appName, QString verName, QString file);


signals:
    void updateListVersion ();
    void connectServer();
    void listVersions ();
    void downloadFile ();
    void downloadFileEnd ();
    void disConnectServer ();
    void clv (QString, QString);

public:
    Network(Log *plog);
    QTcpSocket *server;
    QTimer *timer;
    config *cfg;
    Log *log;
    QStringList listVersion;
    QString uploadFile;
    int countFiles;
    int numberFiles;
    bool isDownload = false;
    QMap <int,QString> *cacheListVersion;

    bool disconnectServer   ();

    ~Network();
};

#endif // NETWORK_H
