#include "server.h"
#include <QObject>
#include <QNetworkInterface>

using namespace std;

Server::Server()
{
    logPrint = new Log(LogPath);
    server_tcp = new QTcpServer(this);
    QTimer *time = new QTimer (this);
    QObject::connect(server_tcp, SIGNAL(newConnection()), this, SLOT(Connect()));
    if(!server_tcp->listen(QHostAddress::Any,port))
    {
        logPrint->print("server not started.     ):", Log::critical_error);
    }
    else
    {
        logPrint->print("server start.     (:", Log::info);
    }

    QObject::connect(time, SIGNAL(timeout()), this, SLOT(tick()));
    //time->start(100);
}

Server::~Server()
{
    foreach(int i,SClients.keys()){
        QTextStream os(SClients[i]);
        os.setAutoDetectUnicode(true);
        os << QDateTime::currentDateTime().toString() << "\n";
        SClients[i]->close();
        SClients.remove(i);
    }
    server_tcp->close();
    qDebug() << QString::fromUtf8("Сервер остановлен!");

    logPrint->end();
}

void Server::Connect ()
{
    logPrint->print ("connct new user", Log::info);
    QTcpSocket* clientSocket = server_tcp->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    client *clientsNew = new client(clientSocket);
    clients.operator <<(clientsNew);
    qDebug () << clients.length();
    return;
}

void Server::tick ()
{
    qDebug ("aswqwe");
}

