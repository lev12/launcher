#include "requestCheckVersionMock.h"

RequestCheckVersionMock::RequestCheckVersionMock(QString App, QString Ver) :
    RequestCheckVersion ()
{
    app = new QString (App);
    ver = new QString (Ver);
    QTimer::singleShot(600, this, &RequestCheckVersionMock::recive);
}

bool RequestCheckVersionMock::parse(QByteArray data)
{

}

void RequestCheckVersionMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    QStringList verList = QDir(resPath).entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach (QString tempStr, verList)
    {
        if (tempStr == *ver)
        {
            NetworkData tempNetData;
            tempNetData.key = *ver;
            tempNetData.value = QVariant (true);
            *netData << tempNetData;
            replyServer(netData);
            return;
        }
    }
    NetworkData tempNetData;
    tempNetData.key = *ver;
    tempNetData.value = QVariant (false);
    *netData << tempNetData;
    replyServer(netData);
    return;
}
