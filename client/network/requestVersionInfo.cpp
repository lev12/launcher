#include "requestVersionInfo.h"

RequestVersionInfo::RequestVersionInfo(QString serverAddress, unsigned short serverPort,QString token,QString app,QString ver) : AbstractRequestForVersion (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app,ver)));
}

bool RequestVersionInfo::parse(QByteArray data)
{
    qDebug () << data;
    QString data_str = data;
    data_str = deleteForRx (data_str);

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
        return true;
    }
    return false;
}
