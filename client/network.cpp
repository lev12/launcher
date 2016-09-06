#include "network.h"

Network::Network()
{
    server = new QTcpSocket();
    server->connectToHost(IPServer,PortServer);
    connectToServer();
    QObject::connect(server, SIGNAL(readyRead()),
                     this, SLOT(readServer()));
}

Network::~Network()
{
    delete server;
}

//  Send to server
bool Network::connectToServer()
{
    QString send = "connect:";
    send.append(QString::number(number_version_launcher));
    send.append(":");

    QTextStream stream (server);
    stream << send;

    server->waitForBytesWritten();
    server->waitForReadyRead();

    return true;
}

bool Network::getVersionListOnServer(QString appName)
{
    QTextStream stream (server);
    stream << "glv:";
    stream << appName;
    stream << ":";

    server->waitForBytesWritten();
    server->waitForReadyRead();

    return true;
}


bool Network::downloadVersion(QString appName, versionType type, int number)
{
    QString send = "file:get:";
    send.append(appName); send.append(":");

    QString tempType;
    switch (type) {
    case pre_alpha:
        tempType = "pre_alpha";
        break;
    case alpha:
        tempType = "alpha";
        break;
    case beta:
        tempType = "beta";
        break;
    case release:
        tempType = "relase";
        break;
    default:
        tempType = "error";
        break;
    }

    send.append(tempType); send.append(":");
    send.append(number); send.append(":");
    QTextStream stream (server);
    stream.operator <<(send);
    return true;
}

bool Network::disconnectServer()
{
    QString send = "glv:";
    QTextStream stream (server);
    stream.operator <<(send);

    return true;
}

//  reception server

void Network::readServer()
{
    QByteArray data = server->readAll();

    if(!parse (data, server))
    {
        QString send = "wrongCmd(";
        send.append(QString (data)); send.append(")");
        QTextStream stream (server);
        stream.operator <<(send);
    }
}

//  parse

bool Network::parse(QByteArray data, QTcpSocket *server)
{
    if (parseConnectServer(data,server)) return true;
    if (parseListVersions (data)) return true;
    if (parseDownloadFile (data, server)) return true;
    if (parseDisconnect (data, server)) return true;

    return false;
}

bool Network::parseConnectServer(QByteArray data, QTcpSocket *server)
{
    QRegExp rx (QString("connect:(\\d+):"));

    if (rx.indexIn(data) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Network::parseListVersions(QByteArray data)
{
    QStringList cmd = QString(data).split(" ");
    bool stream;
    for (int i(0); i<cmd.count(); i++)
    {
        QRegExp rx (QString("ver:rlv:(\\d+):"));
        int countVersions = 0;


        if ((countVersions = rx.indexIn(cmd.at(i))) != -1)
        {
            stream = true;
        }
            else
        {
            if (stream)
            {
                QStringList dataList = cmd.at(i).split('_');
                QString type = dataList.at(0);
                QString number = dataList.at(1);
                QString name = type; name.append(" "); name.append(number);
                listVersion.operator <<(name);

            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool Network::parseDownloadFile(QByteArray data, QTcpSocket *server)
{
    static bool streamDownload;
    static QString nameVersion;

    int pos = 0;

    if (streamDownload)
    {
        static bool download;
        static bool downloadData = true;
        static QFileInfo fileDownload;
        static int fileSize;

        if(downloadData)
        {
            QRegExp rxDl ("file:(.+):(\\d+):(\\d+)"); //file:(\\.+) (\\.+):(\\d+):
            if (rxDl.indexIn(data) != -1)
            {
                QString pathNewVersion = ".\\data/";
                QStringList tempVersionName = nameVersion.split("_");
                pathNewVersion.append(tempVersionName.at(0));
                pathNewVersion.append(" ");
                pathNewVersion.append(tempVersionName.at(1));
                pathNewVersion.append("/");
                pathNewVersion.append(rxDl.cap(1));

                QString versionFilePath (".//data");
                versionFilePath.append(nameVersion);
                QFileInfo versionFile (versionFilePath);
                QFileInfo pathRem(pathNewVersion);
                QString pathCreate (pathRem.absolutePath());
                pathCreate.remove(versionFilePath);
                QDir dir (versionFile.absoluteFilePath());
                dir.mkpath(pathCreate);

                QFile createFile (pathNewVersion);
                createFile.open(QIODevice::WriteOnly);
                createFile.close();
                fileDownload = createFile;

                fileSize = rxDl.cap(2).toInt();
                server->write("file:reception:");

                if(fileSize == 0)
                {
                    server->write("file:accepted");
                    return true;
                }

                downloadData = false;
                download = true;
                return true;
            }
        }
        if (download)
        {
            QString path = fileDownload.absoluteFilePath();
            QFile file(path);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                qDebug ()  << "Not file";
            }
            file.write(data);
            file.flush();

            if (file.size() == fileSize)
            {
                server->write("file:accepted");
                download = false;
                downloadData = true;
            }

            return true;
        }
    }

    QRegExp rx (QString("file:ul:(.+):exe:(.+):(\\d+):(\\d+)"));

    if ((pos = rx.indexIn(data)) == -1)
    {
        return false;
    }
    else
    {
        bool success = true;
        nameVersion = rx.cap(1);

        QDir dir (".\\");
        QString diskName = dir.absolutePath();
        QStringList diskNameList = diskName.split(":/");
        QStorageInfo storage;
        storage.setPath(diskNameList.at(0));
        if (storage.bytesFree() > rx.cap(4).toInt())
        {
            success = false;
        }


        QString send = "file:";
        if (success)
        {
            send.append("ok_reception_file:");
            streamDownload = true;
        }
        else
        {
            send.append("fail:");
        }

        QTextStream streamTxt (server);
        streamTxt.operator <<(send);

        return true;
    }
}

bool Network::parseDisconnect(QByteArray data, QTcpSocket *server)
{
    QRegExp rxDiscon ("disconnect:ser");

    if (rxDiscon.indexIn(data) != -1)
    {
        return true;
    }
    return false;
}