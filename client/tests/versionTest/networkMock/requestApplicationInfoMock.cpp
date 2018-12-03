#include "requestApplicationInfoMock.h"

RequestApplicationInfoMock::RequestApplicationInfoMock(QString &App) :
    RequestApplicationInfo ()
{
    app = new QString (App);
    QTimer::singleShot(600, this, &RequestApplicationInfoMock::recive);
}

bool RequestApplicationInfoMock::parse(QByteArray data)
{

}

void RequestApplicationInfoMock::recive()
{
    QList <NetworkData> *netData = new QList <NetworkData> ();
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(*app);
    if (!QDir(resPath).exists())
    {
        replyServer(netData);
        return;
    }
    resPath.append("/app.cfg");
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
