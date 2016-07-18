#include "server.h"
#include <QObject>

server::server()
{
    server_tcp = new QTcpServer(this);
    QTimer *time = new QTimer (this);

    QObject::connect(server_tcp, SIGNAL(newConnection()), this, SLOT(Connect()));
    if(!server_tcp->listen(QHostAddress::Any,1234))
    {
        printf ("server not started.     ):\n");
    }
    else
    {
        printf("server start.     (:\n");
    }

    QObject::connect(time, SIGNAL(timeout()), this, SLOT(tick()));
    //time->start(100);
}

void server::Connect ()
{
    printf ("\n");
    QTcpSocket* clientSocket=server_tcp->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(ReadClient()));
    return;
}

void server::tick ()
{
    qDebug ("aswqwe");
}

void server::ReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QTextStream stream (clientSocket);
    QString out;
    stream.operator >>(out);
    printf(out.toLocal8Bit());
}

