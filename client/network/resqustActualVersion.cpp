#include "resqustActualVersion.h"

resqustActualVersion::resqustActualVersion(QString serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool resqustActualVersion::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rxClv ("response:actualVersion:(.+)");

    if (rxClv.indexIn(data_str) != -1)
    {
        QString actualVersionOnServer = QString (rxClv.cap(1));

        QList <NetworkData> *response = new QList <NetworkData> ();
        NetworkData netData;
        netData.key = "versionList";
        netData.value = actualVersionOnServer;

        replyServer(response);
        return true;
    }

    return false;
}