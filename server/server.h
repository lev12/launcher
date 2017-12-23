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
#include <QList>
#include <qmath.h>

#include "client.h"
#include "file.h"
#include "log.h"
#include "globalvariable.h"

class Server : public QObject
{
    Q_OBJECT

private:
    QMap<int,QTcpSocket *> SClients;
    QList <client*> clients;
    QTcpServer *server_tcp;
    QTime *timer;
    Log *logPrint;

public slots:
    void Connect ();
    void tick();

public:

    Server();
    ~Server();
};

#endif // SERVER_H
