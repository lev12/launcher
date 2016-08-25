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
#include <qmath.h>

#include "file.h"
#include "log.h"
#include "globalvariable.h"

class Server : public QObject
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

    Server();

    bool parse(QString data, QTcpSocket *client);
    bool parseConnectClient (QString data,QTcpSocket *client);
    bool parseGetListVersions (QString data,QTcpSocket *client);
    bool parseGetVersions (QString data, QTcpSocket *client);
    bool WrongCmd (QString data);

    void FillingFileList (QDir & dir);
    void sizeVersion (QDir & dir);

    ~Server();
};

#endif // SERVER_H
