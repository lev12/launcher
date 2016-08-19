#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include <QRegExp>
#include <QDataStream>
#include <QBuffer>
#include <QTime>

#include "file.h"
#include "log.h"
#include "globalvariable.h"

class server : public QObject
{
    Q_OBJECT

private:
    QTcpServer *server_tcp;
    QTime *timer;
    File verCon;
    Log *logPrint;

public slots:
    void Connect ();
    void tick();
    void ReadClient();

public:
    QMap<int,QTcpSocket *> SClients;
    QList <QFileInfo> FileList;
    long long size;

    server();

    bool parse(QString data, QTcpSocket *client);
    bool parseConnectClient (QString data,QTcpSocket *client);
    bool parseGetListVersions (QString data,QTcpSocket *client);
    bool parseGetVersions (QString data, QTcpSocket *client);

    void FillingFileList (QDir & dir);
    void sizeVersion (QDir & dir);
};

#endif // SERVER_H
