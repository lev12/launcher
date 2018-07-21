#include "requestActualVersion.h"

requestActualVersion::requestActualVersion(QString *serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool requestActualVersion::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rxClv ("response:actualVersion:(.+)");

    if (rxClv.indexIn(data_str) != -1)
    {
        QVariant actualVersionOnServer = QVariant (rxClv.cap(1));

        QList <NetworkData> *response = new QList <NetworkData> ();
        NetworkData netData;
        netData.key = "actualVersion";
        netData.value = actualVersionOnServer;
        response->operator <<(netData);

        replyServer(response);
        return true;
    }

    return false;
}
