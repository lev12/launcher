#include "requestApplicationListMock.h"

RequestApplicationListMock::RequestApplicationListMock() :
    RequestApplicationList ()
{
    QTimer::singleShot(600, this, &RequestApplicationListMock::recive);
}

bool RequestApplicationListMock::parse(QByteArray data)
{

}

void RequestApplicationListMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QStringList verList = QDir(":/versionTestForNetworkData").entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach (QString tempStr, verList)
    {
        NetworkData tempNetData;
        tempNetData.key = "applicationList";
        tempNetData.value = QVariant (tempStr);
        *netData << tempNetData;
    }
    replyServer(netData);
}
