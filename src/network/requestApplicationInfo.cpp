#include "requestApplicationInfo.h"

RequestApplicationInfo::RequestApplicationInfo() : AbstractRequestForApplication ()
{}

RequestApplicationInfo::RequestApplicationInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool RequestApplicationInfo::parse(QByteArray data)
{
    QString data_str = data;
    data_str = deleteForRx (data_str);
    qDebug () << data_str;

    QRegExp rx ("response:info:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        QList <NetworkData> *response = new QList <NetworkData> ();

        QJsonDocument appinfoDoc = QJsonDocument::fromJson(data);\
        QJsonObject appinfoRootObj = appinfoDoc.object();\
        QJsonValue appinfoResponse = appinfoRootObj.value("response");
        QJsonValue appinfoValue = appinfoResponse.toObject().value("info");
        QJsonArray appinfoArray = appinfoValue.toArray();
        for (int i(0);i < appinfoArray.count();i++)
        {
            NetworkData netData;
            QVariantMap tempInfoMap = appinfoArray.at(i).toObject().toVariantMap();
            netData.key = tempInfoMap.keys().at(0);
            netData.value = tempInfoMap.values().at(0);
            response->operator <<(netData);
        }
        replyServer(response);
        return true;
    }
    return false;
}
