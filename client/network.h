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

#include "global_variable.h"
#include "log.h"
#include "config.h"

class Network : public QObject
{
    Q_OBJECT

private:

    bool parse              (QByteArray data, QTcpSocket *server);
    bool parseConnectServer (QByteArray data);
    bool parseListVersions  (QByteArray data);
    bool parseDownloadFile  (QByteArray data, QTcpSocket *server);
    bool parseUploadLog     (QByteArray data, QTcpSocket *server);
    bool parseDisconnect    (QByteArray data);
    bool parseClv           (QByteArray data);

private slots:

    void readServer();
    void connect();
    void disconnect();

public slots:

    bool getClv                 ();
    bool downloadVersion        (QString appName, versionType type,
                                 int number);
    bool getVersionListOnServer (int appName);
    bool sendLog                (QString path);

signals:
    void updateListVersion ();
    void connectServer();
    void listVersions ();
    void downloadFile ();
    void downloadFileEnd ();
    void disConnectServer ();
    void clv (float);
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

    bool connectToServer    ();
    bool disconnectServer   ();

    ~Network();
};

#endif // NETWORK_H
