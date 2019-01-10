#include "applicationNoInstall.h"

ApplicationNoInstall::ApplicationNoInstall(const QString &AppName,Network *network) : AbstractApplication ()
{
    initNet(network);
    initName(AppName);
    if (!net->isConnected())
    {
        QString errorStr("no init version, no net connect");
        throw Exception(12,errorStr);
    }
    requestAppData(net);
}

UiApplication *ApplicationNoInstall::getUiApplication()
{

}

bool ApplicationNoInstall::initName(const QString &name)
{
    appName = new QString (name);
    return true;
}

bool ApplicationNoInstall::initIcon(const QString &path)
{
    appIcon = new QIcon (path);
    return true;
}

bool ApplicationNoInstall::initIcon(const QFile &path)
{
    appIcon = new QIcon (QFileInfo(path).absoluteFilePath());
    return true;
}

bool ApplicationNoInstall::initId(const short &id)
{
    appId = new short;
    *appId = id;
    return true;
}

bool ApplicationNoInstall::initDateRelease(const QDate &date)
{
    appRelease = new QDate (date);
    return true;
}

bool ApplicationNoInstall::initDateLastUpdate(const QDate &date)
{
    appLastUpdate = new QDate (date);
    return true;
}

bool ApplicationNoInstall::initCacheFolder(const short &id)
{
    QString cachePath ("../cache/");
    cachePath.append(QString::number(id));
    if (!QDir(cachePath).exists()) QDir().mkpath(cachePath);
    QDir *cacheDir = new QDir (cachePath);
    cacheDirve = new CacheOnDirve (*cacheDir,nullptr);
    return true;
}

bool ApplicationNoInstall::initSectorIndex(const short &id)
{
    sectorIndex = new int;
    QString idSector ("100");
    idSector.append(QString::number(id));
    *sectorIndex = idSector.toInt();
    return true;
}

bool ApplicationNoInstall::requestAppData(Network *network)
{
    if (!(network->isConnected())) return false;
    AbstractRequest *reqAppInfo = network->getAppInfo(*appName);
    connect(reqAppInfo,&AbstractRequest::replyServer,this,&ApplicationNoInstall::reciveAppInfo);
    return true;
}

bool ApplicationNoInstall::requestAppIcon(Network *network, QUrl &url)
{
    if (!(network->isConnected())) return false;
    AbstractRequest *reqAppInfo = network->getFile(url,QFileInfo(*(cacheDirve->addFile(*sectorIndex,iconFileName))));
    connect(reqAppInfo,&AbstractRequest::replyServer,this,&ApplicationNoInstall::reciveAppInfo);
    return true;
}

void ApplicationNoInstall::reciveAppInfo(QList<NetworkData> *response)
{
    QUrl iconUrl;
    foreach (NetworkData data, *response)
    {
        if (network::keyAppId == data.key)
        {
            iconUrl = data.value.toString();
        }
        if (network::keyAppId == data.key)
        {
            short id = data.value.toString().toShort();
            initId(id);
            initSectorIndex (id);
            cacheDirve->addSector(*sectorIndex);
        }
        if (network::keyAppRelease == data.key)
        {
            QStringList dateStr = data.value.toStringList();
            QDate date (dateStr.at(0).toInt(),
                        dateStr.at(1).toInt(),
                        dateStr.at(2).toInt());
            initDateRelease(date);
        }
        if (network::keyAppLastUpdate == data.key)
        {
            QStringList dateStr = data.value.toStringList();
            QDate date (dateStr.at(0).toInt(),
                        dateStr.at(1).toInt(),
                        dateStr.at(2).toInt());
            initDateLastUpdate(date);
        }
    }
    bool existsIcon = cacheDirve->isExistsKey(*sectorIndex,iconFileName);
    if (existsIcon)
    {
        existsIcon = true;
        initIcon (*cacheDirve->value(*sectorIndex,iconFileName));
    }
    else
    {
        requestAppIcon(net,iconUrl);
    }
}

void ApplicationNoInstall::reciveAppIcon(QList<NetworkData> *response)
{
    if(response->at(0).key == QString("filePath"))
    {
        QString pathIcon = response->at(0).value.toString();
        initIcon(pathIcon);
    }
}
