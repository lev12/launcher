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
    bool parseDisconnect    (QByteArray data);

private slots:

    void readServer();
    void connect();
    void disconnect();


public slots:

    bool downloadVersion        (QString appName, versionType type,
                                 int number);
    bool getVersionListOnServer (QString appName);

signals:
    void updateListVersion ();
    void connectServer();
    void listVersions ();
    void downloadFile ();
    void downloadFileEnd ();
    void disConnectServer ();
public:
    Network(Log *plog);
    QTcpSocket *server;
    QTimer *timer;
    config *cfg;
    Log *log;
    QStringList listVersion;
    int countFiles;
    int numberFiles;

    bool connectToServer    ();
    bool disconnectServer   ();

    ~Network();
};

#endif // NETWORK_H
