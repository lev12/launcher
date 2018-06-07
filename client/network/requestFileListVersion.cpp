#include "requestFileListVersion.h"

RequestFileListVersion::RequestFileListVersion(QString *serverAddress, unsigned short serverPort,QString token,QString app,QString ver) : AbstractRequestForVersion (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app,ver)));
    netReply = getNetReply();
    connect(netReply,QNetworkReply::readyRead, this, RequestFileListVersion::readData);
}

bool RequestFileListVersion::parse(QByteArray data)
{
    QString data_str = data;
    qDebug () << data_str;
    data_str = deleteForRx (data_str);

    QRegExp rx ("response:filesList:(.+)");
    if (rx.indexIn(data_str) != -1)
    {
        QList <NetworkData> *response = new QList <NetworkData> ();
        QStringList fileList = QString(rx.cap(1)).split(",");
        for (int i(0); i < fileList.length(); i++)
        {
            NetworkData netDatatemp;
            netDatatemp.key = QString::number(i);
            netDatatemp.value = fileList.at(i);

            response->operator <<(netDatatemp);
        }
        replyServer(response);
        return true;
    }
    return false;
}

void RequestFileListVersion::readData()
{
    //qDebug () << "reaply data      :" << netReply->readAll();
}
