#include "requestVersionInfoMock.h"

RequestVersionInfoMock::RequestVersionInfoMock(QString &App, QString &Ver) :
    RequestVersionInfo ()
{
    app = new QString(App);
    ver = new QString(Ver);
    QTimer::singleShot(600, this, &RequestVersionInfoMock::recive);
}

bool RequestVersionInfoMock::parse(QByteArray data)
{

}

void RequestVersionInfoMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    if (!QDir(resPath).exists())
    {
        replyServer(netData);
        return;
    }
    resPath.append("/");
    resPath.append(*ver);
    resPath.append("/version_config.cfg");
    if (!QFile(resPath).exists())
    {
        replyServer(netData);
        return;
    }
    Config appCfg (resPath);
    foreach (QString tempStr, appCfg.getConfigKeyName())
    {
        NetworkData tempNetData;
        tempNetData.key = tempStr;
        tempNetData.value = QVariant (appCfg.get(tempStr));
        *netData << tempNetData;
    }
    replyServer(netData);
}
