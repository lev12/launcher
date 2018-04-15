#include "downloader.h"

Downloader::Downloader(QString AppName, QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    appName = AppName;

    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::readServer);
}

Downloader::~Downloader()
{
    qDebug () << "delete";
    QObject::disconnect(manager, &QNetworkAccessManager::finished, this, &Downloader::readServer);
}

QString Downloader::_toSpace(QString str)
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

QString Downloader::spaceTo_(QString str)
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

QString Downloader::deleteForRx (QString data)
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



//Get request
bool Downloader::sendRequest(QString url_str)
{
    if (manager == NULL)
    {
        return false;
    }
    QUrl url(url_str);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
    return true;
}

bool Downloader::requestActualVersion()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getActualVersion?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = ActualVersion;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestVersionList ()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getVersionList?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = VersionList;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestCheckVersion()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.checkVersion?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = CheckVersion;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestExeFileVersion()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getExeFile?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = ExeFileVersion;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestFileListVersion()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getFileList?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = FileListVersion;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestSizeVersion()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getSizeVersion?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = SizeVersion;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestFileSize()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getFileSize?");
    requestUrl.append("app=");
    requestUrl.append(appName);
    downloaderType = FileSize;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

bool Downloader::requestVersionInfo()
{
    QString requestUrl = apiHost;
    requestUrl.append("app.getVersionInfo?");
    requestUrl.append("app=");
    requestUrl.append("Electrical_Simulator");
    requestUrl.append("&version=");
    requestUrl.append("alpha_45");
    downloaderType = VersionInfo;

    if (!sendRequest(requestUrl))
    {
        return false;
    }
    return true;
}

void Downloader::readServer(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    qDebug () << "net     :" << data;

    switch (downloaderType) {
    case ActualVersion:
        parseActualVersion (data);
        break;
    case VersionList:
        parseVersionList (data);
        break;
    case CheckVersion:
        parseCheckVersion (data);
        break;
    case ExeFileVersion:
        parseExeFileVersion (data);
        break;
    case FileListVersion:
        parseFileListVersion (data);
        break;
    case SizeVersion:
        parseSizeVersion (data);
        break;
    case FileSize:
        parseFileSize (data);
        break;
    case VersionInfo:
        parseVersionInfo(data);
        break;
    default:
        QString send = "wrongCmd(";
        send.append(QString (data)); send.append(")");
        qDebug () << send;
        break;
    }
}

bool Downloader::parseActualVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rxClv ("response:actualVersion:(.+)");

    if (rxClv.indexIn(data_str) != -1)
    {
        QString actualVersionOnServer = QString (rxClv.cap(1));
        QStringList actualVersionList = actualVersionOnServer.split("_");

        /*QString send = "current version of the launcher ";
        send.append(actualVersionOnServer);
        log->print(send, Log::info, Log::sreverIn);*/

        response = new QStringList ();
        response->operator <<(actualVersionList.at(0));
        response->operator <<(actualVersionList.at(1));
        qDebug () << response;
        replyServer(response);
        return true;
    }

    return false;
}

bool Downloader::parseVersionList(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rx ("response:versionList:(.+)");

    if (rx.indexIn(data_str) != -1)
    {
        QString str = rx.cap(1);
        QStringList listVerTemp = str.split(",");
        response = new QStringList ();
        foreach (QString temp, listVerTemp)
        {
            response->operator <<( _toSpace(temp));
        }

        replyServer(response);
        return true;
    }

    return false;
}

bool Downloader::parseCheckVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:version:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        bool isVersion;
        if (rx.cap(1) == "true")
        {
            isVersion = true;
        }
        else
        {
            isVersion = false;
        }
        response = new QStringList (QString(isVersion));

        qDebug () << response;
        replyServer(response);
        return true;
    }
    return false;
}

bool Downloader::parseExeFileVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:exeFile:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        response = new QStringList (QString(rx.cap(1)));

        qDebug () << response;
        replyServer(response);
        return true;
    }
    return false;
}

bool Downloader::parseFileListVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:filesList:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        response = new QStringList (QString(rx.cap(1)));

        qDebug () << response;
        replyServer(response);
        return true;
    }
    return false;
}

bool Downloader::parseSizeVersion(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:versionSize:(\\d+)");
    if (rx.indexIn(data_str) != -1)
    {
        response = new QStringList (QString(rx.cap(1)));

        qDebug () << response;
        replyServer(response);
        return true;
    }
    return false;
}

bool Downloader::parseFileSize(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:fileSize:(\\d+)");
    if (rx.indexIn(data_str) != -1)
    {
        response = new QStringList (QString(rx.cap(1)));

        qDebug () << response;
        replyServer(response);
        return true;
    }
    return false;
}

bool Downloader::parseVersionInfo(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:info:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        QStringList resp = QString(rx.cap(1)).split(",");
        response = new QStringList ();

        qDebug () << resp;
        replyServer(&resp);
        return true;
    }
    return false;
}
