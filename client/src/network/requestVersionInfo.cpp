#include "requestVersionInfo.h"

RequestVersionInfo::RequestVersionInfo() : AbstractRequestForVersion ()
{}

RequestVersionInfo::RequestVersionInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app,QString ver) : AbstractRequestForVersion (serverAddress,serverPort)
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

        QJsonDocument verinfoDoc = QJsonDocument::fromJson(data);\
        QJsonObject verinfoRootObj = verinfoDoc.object();\
        QJsonValue verinfoResponse = verinfoRootObj.value("response");
        QJsonValue verinfoValue = verinfoResponse.toObject().value("info");
        QJsonArray verinfoArray = verinfoValue.toArray();
        for (int i(0);i < verinfoArray.count();i++)
        {
            NetworkData netData;
            QVariantMap tempInfoMap = verinfoArray.at(i).toObject().toVariantMap();
            netData.key = tempInfoMap.keys().at(0);
            netData.value = tempInfoMap.values().at(0);
            response->operator <<(netData);
        }
        replyServer(response);
        return true;
    }
    return false;
}
