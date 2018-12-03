#include "abstractRequest.h"

AbstractRequest::AbstractRequest(QObject *parent) : QObject (parent)
{
    emptyRequest = new bool;
    *emptyRequest = false;
}

AbstractRequest::AbstractRequest(QString *ServerAddress, unsigned short ServerPort, QObject *parent) : QObject(parent)
{
    netManager = new QNetworkAccessManager();
    serverAddress = new QString (*ServerAddress);
    serverPort = new unsigned short;
    *serverPort = ServerPort;
    emptyRequest = new bool;
    *emptyRequest = true;

    connect(netManager, &QNetworkAccessManager::finished, this, &AbstractRequest::readServer);
}

AbstractRequest::~AbstractRequest()
{
    disconnect(netManager, &QNetworkAccessManager::finished, this, &AbstractRequest::readServer);
    delete realyServer;
    delete netManager;
}

QString AbstractRequest::getTokenParam(QString token)
{
    QString tokenParam = keyToken;
    tokenParam.append("=");
    tokenParam.append(token);
    return tokenParam;
}

QString AbstractRequest::getApplicationParam(QString app)
{
    QString applicationParam = keyApplication;
    applicationParam.append("=");
    applicationParam.append(spaceTo_(app));
    return applicationParam;
}

QString AbstractRequest::getVersionParam(QString ver)
{
    QString versionParam = keyVersion;
    versionParam.append("=");
    versionParam.append(spaceTo_(ver));
    return versionParam;

}

QString AbstractRequest::getRequestParam(QString token)
{
    QString requestParam("?");
    requestParam.append(getTokenParam(token));
    return requestParam;
}

QString AbstractRequest::getRequestUrl(QString method,QString param)
{
    QString urlstr = "http://";
    urlstr.append(*serverAddress);
    urlstr.append(":");
    urlstr.append(QString::number(*serverPort));
    urlstr.append("/api/method/app.");
    urlstr.append(method);
    urlstr.append(param);
    return urlstr;
}

bool AbstractRequest::sendRequest(QString url)
{
    sendRequestUrl (QUrl(url));
    return true;
}

bool AbstractRequest::sendRequest(QUrl url)
{
    sendRequestUrl (url);
    return true;
}

void AbstractRequest::readServer(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    if (!parse(data))
    {
        qDebug () << "net error   :" << data;
    }
}

QString AbstractRequest::_toSpace(QString str)
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

QString AbstractRequest::spaceTo_(QString str)
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

QString AbstractRequest::deleteForRx (QString data)
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

bool AbstractRequest::isEmptyRequest() const
{
    return *emptyRequest;
}

bool AbstractRequest::sendRequestUrl(QUrl url)
{
    qDebug () << url;
    QNetworkRequest request;
    request.setUrl(url);
    realyServer = netManager->get(request);
    return true;
}

QNetworkReply* AbstractRequest::getNetReply()
{
    return realyServer;
}

QString AbstractRequest::getUrlServer()
{
    QString urlstr = "http://";
    urlstr.append(*serverAddress);
    urlstr.append(":");
    urlstr.append(QString::number(*serverPort));
    return urlstr;
}
