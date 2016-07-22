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
    printf ("connct new user\n");
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
    int idusersocs=clientSocket->socketDescriptor();
    QString out;
    out = clientSocket->readAll();
    printf(out.toStdString().c_str());
    //parse(out,clientSocket);

    QString send = "connect:";
    send.append("1");
    send.append(":");
    QTextStream os(clientSocket);
    os << send;
}

//parse

bool server::parse (QString data,QTcpSocket* client)
{
    if (parseAuthorization(data,client))
        return true;
}

bool server::parseAuthorization (QString data,QTcpSocket* client)
{

    QRegExp exp("connect:(\\d+):");
    if( exp.indexIn(data) == -1 )
        return false;

    exp.cap(1).toInt();

    return true;
}

bool server::parseGetListVersions (QString data,QTcpSocket* client)
{

}

