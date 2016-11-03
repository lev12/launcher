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
#include "config.h"

class Network : public QObject
{
    Q_OBJECT

private:
    QTcpSocket *server;

    bool parse              (QByteArray data, QTcpSocket *server);
    bool parseConnectServer (QByteArray data, QTcpSocket *server);
    bool parseListVersions  (QByteArray data);
    bool parseDownloadFile  (QByteArray data, QTcpSocket *server);
    bool parseDisconnect    (QByteArray data, QTcpSocket *server);

private slots:

    void readServer();
    void connect();
    void disconnect();
    void netError(QAbstractSocket::SocketError);

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
    Network();

    QTimer *timer;
    config *cfg;
    QStringList listVersion;
    int countFiles;
    int numberFiles;

    bool connectToServer    ();
    bool disconnectServer   ();

    ~Network();
};

#endif // NETWORK_H
