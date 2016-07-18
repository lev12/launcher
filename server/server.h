#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include "file.h"

class server : public QObject
{
    Q_OBJECT

private:
    QTcpServer *server_tcp;
    QTime *timer;

public slots:
    void Connect ();
    void tick();
    void ReadClient();
public:
    QMap<int,QTcpSocket *> SClients;
    server();
};

#endif // SERVER_H
