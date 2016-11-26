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

    bool parse(QByteArray data, QTcpSocket *client);
    bool parseConnectClient (QByteArray data,QTcpSocket *client);
    bool parseGetListVersions (QByteArray data,QTcpSocket *client);
    bool parseGetVersions (QByteArray data, QTcpSocket *client);
    bool parseDownloadLog (QByteArray data, QTcpSocket *client);
    bool parseDisconnect (QByteArray data, QTcpSocket *client);
    bool WrongCmd (QString data);
    QString streamDataFile (QString filePath, int sizeFile, int countBlock);

    void FillingFileList (QDir & dir);
    void sizeVersion (QDir & dir);

    ~Server();
};

#endif // SERVER_H
