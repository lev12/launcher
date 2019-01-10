#include "requestVersionListMock.h"

RequestVersionListMock::RequestVersionListMock(QString &serverAddress, unsigned short serverPort, QString &token, QString &App) :
    RequestVersionsList()
{
    app = new QString (App);
    QTimer::singleShot(600, this, &RequestVersionListMock::recive);
}

bool RequestVersionListMock::parse(QByteArray data)
{

}

void RequestVersionListMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    QStringList verList = QDir(resPath).entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach (QString tempStr, verList)
    {
        NetworkData tempNetData;
        tempNetData.key = "versionList";
        tempNetData.value = QVariant (tempStr);
        *netData << tempNetData;
    }
    replyServer(netData);
}
