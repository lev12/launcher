#include "requestVersionsList.h"

RequestVersionsList::RequestVersionsList(QString *serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool RequestVersionsList::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rx ("response:versionList:(.+)");

    if (rx.indexIn(data_str) != -1)
    {
        QString str = rx.cap(1);
        QStringList listVerTemp = str.split(",");
        QList <NetworkData> *response =  new QList <NetworkData> ();
        foreach (QString temp, listVerTemp)
        {
            NetworkData netData;
            netData.key = "versionList";
            netData.value = QVariant(_toSpace(temp));
            response->operator <<(netData);
        }


        replyServer(response);
        return true;
    }

    return false;
}
