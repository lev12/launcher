#include "network.h"

Network::Network(Log *plog)
{
    log = plog;
    cfg = new config();

    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Network::readServer);
    //connect(reply, &QIODevice::readyRead, this, &Network::readServer);
}

Network::~Network()
{
    delete server;
}

QString Network::_toSpace(QString str)
{
    QStringList list = str.split('_');
    QString ret = list.at(0);
    list.takeAt(0);
    foreach (QString tempItem, list) {
        ret.append(" ");
        ret.append(tempItem);
    }
    return ret;
}

QString Network::spaceTo_(QString str)
{
    QStringList list = str.split(' ');
    QString ret = list.at(0);
    list.takeAt(0);
    foreach (QString tempItem, list) {
        ret.append("_");
        ret.append(tempItem);
    }
    return ret;
}

QString Network::deleteForRx (QString data)
{
    QString data_str = data;
    data_str.remove(data_str.size()-2,2);
    QStringList data_list = data_str.split("\"");
    data_str.clear();
    foreach (QString temp, data_list) {
        data_str.append(temp);
    }

    data_list = data_str.split("}");
    data_str.clear();
    foreach (QString temp, data_list) {
        data_str.append(temp);
    }
    data_list = data_str.split("{");
    data_str.clear();
    foreach (QString temp, data_list) {
        data_str.append(temp);
    }
    data_list = data_str.split("[");
    data_str.clear();
    foreach (QString temp, data_list) {
        data_str.append(temp);
    }
    data_list = data_str.split("]");
    data_str.clear();
    foreach (QString temp, data_list) {
        data_str.append(temp);
    }
    return data_str;
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

void Network::readServer(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    if(!parse (data, server))
    {
        /*QString send = "wrongCmd(";
        send.append(QString (data)); send.append(")");
        QTextStream stream (server);
        stream.operator <<(send);*/
    }
}
//slots get request
bool Network::getVersionList (QString appName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getVersionList?app=");
    str_url.append(spaceTo_(appName));
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::getActualVersion (QString appName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getActualVersion?app=");
    str_url.append(appName);
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::getExeFile(QString appName, QString verName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getExeFile?app=");
    str_url.append(appName);
    str_url.append("&version=");
    str_url.append(verName);
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::getSizeVersion(QString appName, QString verName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getSizeVersion?app=");
    str_url.append(appName);
    str_url.append("&version=");
    str_url.append(verName);
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::getFileList(QString appName, QString verName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getFileList?app=");
    str_url.append(appName);
    str_url.append("&version=");
    str_url.append(verName);
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::checkVersion(QString appName, QString verName)
{
    QString str_url = _Host;
    str_url.append("api/method/app.checkVersion?app=");
    str_url.append(appName);
    str_url.append("&version=");
    str_url.append(verName);

    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

    return true;
}

bool Network::getVersion(QString appName, QString verName)
{
    downloadApp = "Electrical_Simulator";
    downloadVersion = "alpha_45";
    checkVersion(appName, verName);
}

bool Network::getFile(QString appName, QString verName, QString file)
{
    QString str_url = _Host;
    str_url.append("app/");
    str_url.append(appName);
    str_url.append("/");
    str_url.append(verName);
    file.remove(0,1);
    str_url.append(file);

    QStringList data_list = str_url.split("\\/");
    str_url.clear();
    foreach (QString temp, data_list) {
        str_url.append(temp);
        str_url.append("/");
    }
    str_url.remove(str_url.length()-1,1);
    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    reply = manager->get(request);
    connect(reply, &QIODevice::readyRead, this, Network::downloadFileRS);
    //connect(reply, &QNetworkReply::finished, this, Network::downloadFileRS);

    QString pathNewVersion = ".//data/";
    pathNewVersion.append(appName);
    pathNewVersion.append("/");
    pathNewVersion.append(verName);
    pathNewVersion.append("/");
    QFileInfo info (pathNewVersion);
    QDir dir (info.absolutePath());
    pathNewVersion.append(QString(files[filesNum]).remove(0,2));
    QFileInfo infoi (pathNewVersion);
    dir.mkpath(infoi.absolutePath());


    createFile = new QFile (infoi.absoluteFilePath());
    createFile->open(QIODevice::WriteOnly);
    qDebug () << infoi.absolutePath();
}

bool Network::getFileSize (QString appName, QString verName, QString file)
{
    QString str_url = _Host;
    str_url.append("api/method/app.getFileSize?app=");
    str_url.append(appName);
    str_url.append("&version=");
    str_url.append(verName);
    str_url.append("&file=");

    QString fileTemp;
    QStringList data_list = file.split("\\/");
    fileTemp.clear();
    foreach (QString temp, data_list) {
        fileTemp.append(temp);
        fileTemp.append("/");
    }
    fileTemp.remove(fileTemp.length()-1,1);
    str_url.append(fileTemp);

    qDebug () << str_url;
    QUrl url(str_url);
    QNetworkRequest request;
    request.setUrl(url);
    reply = manager->get(request);
}

//  parse

bool Network::parse(QByteArray data, QTcpSocket *server)
{
    if (download)
    {
        if (parseFileSize(data)) return true;
        if (parseDownloadFile (data, server)) return true;
    }
    if (parseListVersions (data)) return true;
    if (parseAcualVersion (data)) return true;
    if (parseDownloadFile (data, server)) return true;
    //if (parseUploadLog(data, server)) return true;

    return false;
}

bool Network::parseListVersions(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rx ("response:versionList:(.+)");
    bool s = rx.indexIn(data_str) != -1;
    qDebug () << s << rx.errorString();
    if (rx.indexIn(data_str) != -1)
    {
        qDebug () << rx.cap(1);
        QString str = rx.cap(1);
        QStringList listVerTemp = str.split(",");
        QStringList verList;
        foreach (QString temp, listVerTemp) {
            verList << _toSpace(temp);
        }
        listVersion = verList;
        listVersions ();

        return true;
    }


    return false;
}

bool Network::parseDownloadFile(QByteArray data, QTcpSocket *server)
{
    static int action = 0;
    static bool success = false;
    QString data_str = data;
    data_str = deleteForRx (data_str);


    if (action == 0)
    {
        QRegExp rx ("response:version:(.+)");
        if (rx.indexIn(data_str) != -1)
        {
            download = true;
            action = 1;
            qDebug () << download << action;
            getSizeVersion ("Electrical_Simulator", "alpha_45");
            return true;
        }
        return false;
    }

    static int sizeVsrion;
    if (action == 1)
    {
        QRegExp rx ("response:versionSize:(\\d+)");
        if (rx.indexIn(data_str) != -1)
        {
            sizeVsrion = rx.cap(1).toInt();
            qDebug () << sizeVsrion;
            QDir dir (".\\");
            QString diskName = dir.absolutePath();
            QStringList diskNameList = diskName.split(":/");
            QStorageInfo storage;
            storage.setPath(diskNameList.at(0));
            if (storage.bytesFree() > sizeVsrion)
            {
                success = false;
            }
            else
            {
                success = true;

            }
            qDebug () << data_str;
            getExeFile ("Electrical_Simulator", "alpha_45");
            action = 2;
            return true;
        }
        return false;
    }

    static QString exe;
    if (action == 2)
    {
        QRegExp rx ("response:exeFile:(.+)");
        if (rx.indexIn(data_str) != -1)
        {
            exe = rx.cap(1);
            action = 3;
            qDebug () << data_str;
            getFileList ("Electrical_Simulator", "alpha_45");
            return true;
        }
        return false;
    }

    if (action == 3)
    {
        QRegExp rx ("response:filesList:(.+)");
        if (rx.indexIn(data_str) != -1)
        {
            QString str = rx.cap(1);
            files = str.split(",");
            action = 4;
            filesNum = 0;
            getFileSize(downloadApp, downloadVersion, files[filesNum]);
            return true;
        }
        return false;
    }

    if (action == 4)
    {
        if (files.length()-1 == filesNum)
        {
            qDebug () << "download complit";
        }
        else if (createFile->size() == fileSize)
        {
            qDebug () << files.length() << filesNum;
            if (files.length()-1 > filesNum)
            {
                createFile->close();
                filesNum++;
                getFileSize(downloadApp, downloadVersion, files[filesNum]);
            }
            return true;
        }
    }
}

bool Network::downloadFileRS()
{

    static int numl = 0;
    if (filesNum == 733)
    {
        qDebug () << "jdfjdhfdhid";
    }
    qDebug () << numl << createFile->fileName() << createFile->size();
    createFile->write(reply->readAll());
    numl++;

    qDebug () << fileSize;
    qDebug () << files.length() << filesNum;


    return true;
}

bool Network::parseFileSize(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:fileSize:(\\d+)");

    if (rx.indexIn(data_str) != -1)
    {
        fileSize = rx.cap(1).toInt();

        getFile("Electrical_Simulator", "alpha_45", files[filesNum]);
        return true;
    }

    return false;
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

bool Network::parseAcualVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    qDebug () << data_str;
    QRegExp rxClv ("response:actualVersion:(.+)");

    if (rxClv.indexIn(data_str) != -1)
    {
        QString actualVersionOnServer = QString (rxClv.cap(1));
        QStringList actualVersionList = actualVersionOnServer.split("_");

        QString send = "current version of the launcher ";
        send.append(actualVersionOnServer);
        log->print(send, Log::info, Log::sreverIn);

        clv(actualVersionList.at(0), actualVersionList.at(1));
        qDebug () << actualVersionList.at(0) << actualVersionList.at(1);
        return true;
    }
    return false;
}
