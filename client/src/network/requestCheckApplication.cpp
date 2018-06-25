#include "requestCheckApplication.h"

RequestCheckApplication::RequestCheckApplication(QString *serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool RequestCheckApplication::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:application:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        bool isApplication;
        if (rx.cap(1) == "true")
        {
            isApplication = true;
        }
        else
        {
            isApplication = false;
        }
        QList <NetworkData> *response = new QList <NetworkData> ();
        NetworkData netData;
        netData.key = "application";
        netData.value = QString(isApplication);
        replyServer(response);
        return true;
    }
    return false;
}
