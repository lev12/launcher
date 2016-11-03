#include "network.h"

Network::Network()
{
    cfg = new config();
    server = new QTcpSocket();
    connect();
    connectToServer();
    QObject::connect(server, SIGNAL(readyRead()), this, SLOT(readServer()), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(disconnected()), this, SLOT(disconnect()), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(error(QAbstractSocket::SocketError)),
                       this, SLOT(netError(QAbstractSocket::SocketError)), Qt::DirectConnection);
}

Network::~Network()
{
    delete server;
}

// Error net
void Network::netError(QAbstractSocket::SocketError)
{
    qDebug () << server->errorString();
}

// Disconnect from the server
void Network::disconnect()
{
    qDebug () << "disConnect";
    disConnectServer();
    parseDownloadFile(QByteArray ("file:stop:downloading:from:server:"), server);
}

void Network::connect()
{
    qDebug () << "connect";
    server->connectToHost(cfg->get("IPServer"),cfg->get("PortServer").toInt());
    connectToServer();
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
    server->waitForReadyRead(300);
    return true;
}

bool Network::getVersionListOnServer(QString appName)
{
    QTextStream stream (server);
    stream << "glv:";
    stream << appName;
    stream << ":";

    server->waitForReadyRead(100);

    return true;
}


bool Network::downloadVersion(QString appName, versionType type, int number)
{
    QString send = "file:get:";
    send.append(appName); send.append(":");

    QString tempType;
    switch (type) {
    case pre_alpha:
        tempType = "pre-alpha";
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
    send.append(QString::number(number)); send.append(":");
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
    if (parseDownloadFile (data, server)) return true;
    if (parseListVersions (data)) return true;
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
        connectServer();
        return true;
    }
}

bool Network::parseListVersions(QByteArray data)
{
    QStringList cmd = QString(data).split(" ");
    bool stream;
    for (int i(0); i<cmd.count(); i++)
    {
        QRegExp rx ("ver:rlv:(\\d+):");

        if (rx.indexIn(cmd.at(i)) != -1)
        {
            stream = true;
        }
        else
        {
            if (stream)
            {
                qDebug () << "              dwnload4";
                QStringList dataList = cmd.at(i).split('_');
                QString type = dataList.at(0);
                QString number = dataList.at(1);
                QString name = type; name.append(" "); name.append(number);
                qDebug () << name;
                listVersion.operator <<(name);

            }
            else
            {
                return false;
            }
        }
    }

    listVersions ();
    return true;
}

bool Network::parseDownloadFile(QByteArray data, QTcpSocket *server)
{
    static bool streamDownload;
    static QString nameApp;
    static QString nameVersion;

    int pos = 0;

    if (streamDownload)
    {
        static bool download;
        static bool downloadData = true;
        static QFileInfo fileDownload;
        static int fileSize;

        QRegExp rxStop ("file:stop:downloading:from:server:");

        if (rxStop.indexIn(data) != -1)
        {
            download = false;
            downloadData = false;
            fileDownload.~QFileInfo();
            fileSize = 0;
            downloadFileEnd();
        }

        if (downloadData)
        {
            QRegExp rxDl ("file:(.+):(\\d+):(\\d+)");
            if (rxDl.indexIn(data) != -1)
            {
                QString pathNewVersion = ".\\data/";
                pathNewVersion.append(nameApp);
                pathNewVersion.append("/");
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
                    numberFiles++;
                    downloadFile();
                    return true;
                }

                downloadData = false;
                download = true;
                return true;
            }
            QRegExp rxEnd ("file:ulEnd:");
            if (rxEnd.indexIn(data) != -1)
            {
                streamDownload = false;
                downloadData = true;
                download = false;
                fileDownload.~QFileInfo();
                downloadFileEnd ();
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
                numberFiles++;
                downloadFile();
                server->write("file:accepted");
                download = false;
                downloadData = true;
            }

            return true;
        }
    }

    QRegExp rx (QString("file:ul:(.+):(.+):exe:(.+):(\\d+):(\\d+)"));

    if ((pos = rx.indexIn(data)) == -1)
    {
        return false;
    }
    else
    {
        countFiles = rx.cap(4).toInt();
        bool success = true;
        nameVersion = rx.cap(2);
        nameApp = rx.cap(1);

        QDir dir (".\\");
        QString diskName = dir.absolutePath();
        QStringList diskNameList = diskName.split(":/");
        QStorageInfo storage;
        storage.setPath(diskNameList.at(0));
        if (storage.bytesFree() > rx.cap(5).toInt())
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
        disConnectServer();
        return true;
    }
    return false;
}
