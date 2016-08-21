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
    logPrint->end();
}

void Server::Connect ()
{
    logPrint->print ("connct new user", Log::info);
    QTcpSocket* clientSocket=server_tcp->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(ReadClient()));
    return;
}

void Server::tick ()
{
    qDebug ("aswqwe");
}

void Server::ReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int idusersocs=clientSocket->socketDescriptor();
    QString out;
    out = clientSocket->readAll();
    if (WrongCmd(out))
    {
        logPrint->print(out, Log::error, Log::clientIn);
    }
    else
    {
        logPrint->print(out, Log::info, Log::clientIn);
        parse(out,clientSocket);
    }
}

//parse

bool Server::parse (QString data,QTcpSocket* client)
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

bool Server::parseConnectClient (QString data,QTcpSocket* client)
{
    int versionClient;
    int pos = 0;
    QRegExp rx ("connect:(\\d):");

    if ((pos = rx.indexIn(data, pos)) == -1)
    {
        return false;
    }

    QString send = "connect:";
    send.append("8");
    send.append(":");
    QTextStream os(client);
    os << send;
    logPrint->print (send, Log::info, Log::sreverOut);

    return true;
}

bool Server::parseGetListVersions (QString data,QTcpSocket* client)
{
    int pos = 0;
    QRegExp rx ("glv:");

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
    logPrint->print (send, Log::info, Log::sreverOut);
    return true;
}

bool Server::parseGetVersions (QString data, QTcpSocket *client)
{
    static bool stream;
    static bool streamTransfer;
    static bool streamData;
    int pos = 0;

    QRegExp rx ("file:get:(\\w+) (\\d+)");

    if ((pos = rx.indexIn(data, pos)) != -1)
    {
        QString pathFileCount = ".\\data/"; pathFileCount.append(rx.cap(1));
        pathFileCount.append(" "); pathFileCount.append(rx.cap(2));

        QDir dir (pathFileCount);
        FileList.clear();
        FillingFileList(dir);
        int countVersions = FileList.length();
        sizeVersion(dir);
        int size_temp = size;

        QTextStream stream(client);
        QString send;


        if(!verCon.checkVersion(rx.cap(1),rx.cap(2)))
        {
            printf("no version\n");
            logPrint->print("no version", Log::error);
        }

        QString tempName = rx.cap(1); tempName.append("_"); tempName.append(rx.cap(2));
        send.append("file:ul:"); send.append(tempName); send.append(":");
        send.append("exe:"); send.append(verCon.getExeFile(verCon.getFile(rx.cap(1),rx.cap(2))));
        send.append(":"); send.append(QString::number(countVersions));
        send.append(":"); send.append(QString::number(size_temp));
        logPrint->print (send, Log::info, Log::sreverOut);
        stream.operator <<(send);

        return true;
    }



    QRegExp rxFail ("file:fail:");

    if ((pos = rxFail.indexIn(data, pos)) != -1)
    {
        stream = false;
        return true;
    }

    QRegExp rxSuc ("file:ok_reception_file:");

    if ((pos = rxSuc.indexIn(data)) != -1)
    {
        stream = true;
        streamData = true;
    }

    if (stream)
    {
        static int countBlock;
        static int numberFile;
        static QFileInfo streamFile;
        streamFile = FileList.at(numberFile);

        QRegExp rxRec ("file:reception:");

        if ((pos = rxRec.indexIn(data)) != -1)
        {
            streamTransfer = true;
        }

        if (streamTransfer)
        {

            QFile file(streamFile.absoluteFilePath());
            file.open(QIODevice::ReadOnly);
            QByteArray buffer;

            for (int i(0); i <= countBlock; i++)
            {
                buffer = file.read(1024);

                qDebug () << buffer;
                logPrint->print (buffer, Log::info, Log::sreverOut);

                client->write(buffer);
                client->flush();
            }

        }

        if (streamData)
        {
            QTextStream sendStream (client);


            QString nameFile = streamFile.fileName();
            int sizeFile = streamFile.size();

            countBlock = qFloor(sizeFile/1024);

            QString send = "file:";
            send.append(nameFile); send.append(":");
            send.append(QString::number(sizeFile)); send.append(":");
            send.append(QString::number(countBlock)); send.append(":");

            sendStream.operator <<(send);
            logPrint->print (send, Log::info, Log::sreverOut);
            streamData = false;
            return true;
        }


        return false;

    }
    return false;
}

bool Server::WrongCmd (QString data)
{
    QRegExp rx ("wrongCmd");
    if (rx.indexIn(data) == -1) return false;

    return true;
}

void Server::FillingFileList (QDir & dir)
{
    QList <QString> lstDirs = dir.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    QList <QFileInfo> lstFiles = dir.entryInfoList(QDir::Files);

    FileList.operator <<(lstFiles);

    foreach (QString tempDir, lstDirs) {
        QString entryAbsPath = dir.absolutePath() + "/" + tempDir;
        QDir dr(entryAbsPath);
        FillingFileList(dr);
    }

    return;
}

void Server::sizeVersion (QDir & dir)
{
    size = 0;
    foreach (QFileInfo item, FileList) {
        size = size + item.size() ;
    };

    return;
}
