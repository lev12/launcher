#include "requestAppicationInfo.h"

requestapplicationInfo::requestapplicationInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool requestapplicationInfo::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    qDebug () << data;
    QRegExp rx ("response:info:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        QList <NetworkData> *response = new QList <NetworkData> ();
        QStringList verinfo = QString(rx.cap(1)).split(",");
        foreach (QString infotemp, verinfo) {
            NetworkData tempData;
            tempData.key = "info";
            tempData.value = infotemp;

            response->push_back(tempData);
        }
        replyServer(response);
        qDebug () << response;
        return true;
    }
    return false;
}
