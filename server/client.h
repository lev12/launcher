#ifndef CLIENT_H
#define CLIENT_H

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
#include <QDir>

#include "file.h"
#include "log.h"
#include "globalvariable.h"

class client : QObject
{
    Q_OBJECT
public slots:
    void ReadClient();

public:
    File verCon;
    Log *logPrint;
    QList <QFileInfo> FileList;
    long long size;

    QList <File> AppList;
    void fillingAppList ();
    File foundApp(QString appName);
    //File **fileTemp;

    client(QTcpSocket *socket);

    bool parse(QByteArray data, QTcpSocket *client);
    bool parseConnectClient (QByteArray data,QTcpSocket *client);
    bool parseGetListVersions (QByteArray data,QTcpSocket *client);
    bool parseGetVersions (QByteArray data, QTcpSocket *client);
    bool parseDownloadLog (QByteArray data, QTcpSocket *client);
    bool parseDisconnect (QByteArray data, QTcpSocket *client);
    bool parseCVL (QByteArray data, QTcpSocket *client);
    bool WrongCmd (QString data);
    QString streamDataFile (QString filePath, int sizeFile, int countBlock);

    void FillingFileList (QDir & dir);
    void sizeVersion (QDir & dir);

    QString add_ (QString str);
    QString delete_ (QString str);
};

#endif // CLIENT_H
