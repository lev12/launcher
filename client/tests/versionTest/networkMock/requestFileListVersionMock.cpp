#include "requestFileListVersionMock.h"

RequestFileListVersionMock::RequestFileListVersionMock(QString App, QString Ver) :
    RequestFileListVersion ()
{
    app = new QString (App);
    ver = new QString (Ver);
    QTimer::singleShot(600, this, &RequestFileListVersionMock::recive);
}

bool RequestFileListVersionMock::parse(QByteArray data)
{

}

void RequestFileListVersionMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    resPath.append("/");
    resPath.append(*ver);
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
