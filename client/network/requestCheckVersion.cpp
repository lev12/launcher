#include "requestCheckVersion.h"

RequestCheckVersion::RequestCheckVersion(QString serverAddress, unsigned short serverPort,QString token,QString app,QString ver) : AbstractRequestForVersion (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app,ver)));
}

bool RequestCheckVersion::parse(QByteArray data)
{
    QString datastr = data;
    datastr = deleteForRx(datastr);
    QRegExp rx ("response:(version):(.+)");
    if (rx.indexIn(datastr) != -1)
    {
        bool isFoundVersion;
        if (rx.cap(2) == "true")
        {
            isFoundVersion = true;
        }
        else
        {
            isFoundVersion = false;
        }
        QList<NetworkData> *response;
        NetworkData responseData;
        responseData.key = rx.cap(1);
        responseData.value = QString(isFoundVersion);
        response = new QList<NetworkData>;
        response->push_back(responseData);

        replyServer(response);
        return true;
    }
    return false;
}
