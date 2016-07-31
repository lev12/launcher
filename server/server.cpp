#include "server.h"
#include <QObject>
#include <QNetworkInterface>

using namespace std;

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
    parse(out,clientSocket);
}

//parse

bool server::parse (QString data,QTcpSocket* client)
{
    if (parseConnectClient(data,client))
    {
        return true;
    }else if (parseGetListVersions(data,client))
    {
        return true;
    }else if (parseGetVersions(data,client))
    {
        return true;
    }

    return false;
}

bool server::parseConnectClient (QString data,QTcpSocket* client)
{
    int versionClient;
    int pos = 0;
    QRegExp rx ("connect:(\\d):\n");

    if ((pos = rx.indexIn(data, pos)) == -1)
    {
        return false;
    }

    QString send = "connect:";
    send.append("8");
    send.append(":");
    QTextStream os(client);
    os << send;

    return true;
}

bool server::parseGetListVersions (QString data,QTcpSocket* client)
{
    int pos = 0;
    QRegExp rx ("glv\n");

    if ((pos = rx.indexIn(data, pos)) == -1)
    {
        return false;
    }

    QString send = "ver:rlv:";
    send.append(QString::number(verCon.versions.length()));
    send.append(":");


    for (QFileInfo temp : verCon.getVersonsList())
    {
        QStringList str = verCon.getVersionName(temp).split(" ");
        send.append(" "); send.append(str[0]); send.append("_"); send.append(str[1]);
    }



    QTextStream os (client);
    os << send;
    return true;
}

bool server::parseGetVersions (QString data, QTcpSocket *client)
{
    int pos = 0;
    QRegExp rx ("file:get:(\\w+) (\\d+)");

    if ((pos = rx.indexIn(data, pos)) != -1)
    {
        QTextStream stream(client);
        QString send;
        int countVersions;

        if(!verCon.checkVersion(rx.cap(1),rx.cap(2)))
        {
            printf("no version/n");
        }

        QString tempName = rx.cap(1); tempName.append("_"); tempName.append(rx.cap(2));
        send.append("file:ul:"); send.append(tempName); send.append(":");
        send.append("exe:"); send.append(verCon.getExeFile(verCon.getFile(rx.cap(1),rx.cap(2))));
        //send.append(countVersions);
        stream.operator <<(send);
        return true;
    }
    return false;
    /*QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    QString send;

    if(!verCon.checkVersion(rx.cap(1),rx.cap(2)))
    {
        printf("no version/n");
    }

    QString tempName = rx.cap(1); tempName.append("_"); tempName.append(rx.cap(2));
    send.append("file:ul:"); send.append(tempName); send.append(" ");
    //out.operator <<(send);*/
}
