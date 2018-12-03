#include "requestActualVersionMock.h"

RequestActualVersionMock::RequestActualVersionMock(QString &App) :
    RequestActualVersion ()
{
    app = new QString (App);
    QTimer::singleShot(600, this, &RequestActualVersionMock::recive);
}

bool RequestActualVersionMock::parse(QByteArray data)
{

}

void RequestActualVersionMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    QStringList verList = QDir(resPath).entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    QList <AbstractVersion*> versionsList;
    foreach (QString tempStr, verList)
    {
        VersionNoInstall *version = new VersionNoInstall(*app,tempStr);
        versionsList << version;
    }
    versionsList = VersionController::sortVersionList(versionsList);

    NetworkData tempNetData;
    tempNetData.key = "actualVersion";
    tempNetData.value = QVariant (versionsList.at(0)->getFullName());
    *netData << tempNetData;

    replyServer(netData);

}
