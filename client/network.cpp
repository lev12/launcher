#include "network.h"

Network::Network(Log *plog)
{
    log = plog;
    cfg = new config();
    server = new QTcpSocket();
    connect();
    connectToServer();
    QObject::connect(server, SIGNAL(readyRead()), this, SLOT(readServer()));
    QObject::connect(server, SIGNAL(disconnected()), this, SLOT(disconnect()));
}

Network::~Network()
{
    delete server;
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
    if (!isDownload)
    {
        QTextStream stream (server);
        stream << "glv:";
        stream << appName;
        stream << ":";

        server->waitForReadyRead(100);

    }
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

bool Network::sendLog(QString path)
{
    qDebug () << "send log";
    QFileInfo file (path);
    if (!file.exists())
    {
        return false;
    }

    uploadFile = path;
    QString send = "log:";
    send.append(file.fileName());
    send.append(":");
    send.append(QString::number(file.size()));
    send.append(":");
    send.append(QString::number(qFloor(file.size()/8192)+1));
    send.append(":");

    qDebug () << send;

    server->write(send.toLocal8Bit());
    server->waitForBytesWritten();
    server->waitForReadyRead();

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
    if (parseConnectServer(data)) return true;
    if (parseDownloadFile (data, server)) return true;
    if (parseUploadLog(data, server)) return true;
    if (parseListVersions (data)) return true;
    if (parseDisconnect (data)) return true;

    return false;
}

bool Network::parseConnectServer(QByteArray data)
{
    QRegExp rx (QString("connect:(\\d+):"));

    if (rx.indexIn(data) == -1)
    {
        return false;
    }
    else
    {
        log->print("connect", Log::info, Log::sreverIn);
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
            log->print("list_versions_start", Log::info);
        }
        else
        {
            if (stream)
            {
                QStringList dataList = cmd.at(i).split('_');
                QString type = dataList.at(0);
                QString number = dataList.at(1);
                QString tempName = type; tempName.append("_"); tempName.append(number);
                log->print(tempName, Log::info, Log::sreverIn);
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
    log->print("list_versions_end", Log::info);

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
            isDownload = false;
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
                QString name = "file_name_";
                name.append(rxDl.cap(1));
                name.append("_size_");
                name.append(rxDl.cap(2));
                name.append("_count_block_");
                name.append(rxDl.cap(3));
                log->print(name, Log::info, Log::sreverIn);

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
                log->print("download_end");
                streamDownload = false;
                downloadData = true;
                download = false;
                fileDownload.~QFileInfo();
                downloadFileEnd ();
                isDownload = false;
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
            log->print("download_start");
            send.append("ok_reception_file:");
            streamDownload = true;
            isDownload = true;
        }
        else
        {
            log->print("download_fail");
            send.append("fail:");
        }

        QTextStream streamTxt (server);
        streamTxt.operator <<(send);

        return true;
    }
}

bool Network::parseUploadLog(QByteArray data, QTcpSocket *server)
{
    if (data == "file:error:")
    {
        return true;
    }

    QFile file (uploadFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug () << "not open file upload";
    }

    if (data == "log:accepted:" || data == "log:reception:")
    {
        static int countBlock = qFloor(file.size()/8192)+1;
        static int numberBlock;

        if (countBlock != numberBlock)
        {
            QByteArray buffer;
            buffer = file.read(8192);
            server->write(buffer);
            server->waitForBytesWritten();
            server->flush();
            numberBlock++;
            return true;
        }
        else
        {
            server->write("log:upload:end:");
            file.close();
            return true;
        }
     }
    return false;
}

bool Network::parseDisconnect(QByteArray data)
{
    QRegExp rxDiscon ("disconnect:ser");

    if (rxDiscon.indexIn(data) != -1)
    {
        log->print("disconnect_server", Log::info, Log::sreverIn);
        disConnectServer();
        return true;
    }
    return false;
}
