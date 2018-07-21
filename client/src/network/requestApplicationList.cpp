#include "requestApplicationList.h"

RequestApplicationList::RequestApplicationList(QString *serverAddress, int serverPort, QString token) : AbstractRequest (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token)));
}

bool RequestApplicationList::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    QRegExp rx ("response:applicationList:(.+)");

    if (rx.indexIn(data_str) != -1)
    {
        QString str = rx.cap(1);
        QStringList listVerTemp = str.split(",");
        QList <NetworkData> *response =  new QList <NetworkData> ();
        foreach (QString temp, listVerTemp)
        {
            NetworkData netData;
            netData.key = "applicationList";
            netData.value = QVariant(_toSpace(temp));
            response->operator <<(netData);
        }


        replyServer(response);
        return true;
    }

    return false;
}
