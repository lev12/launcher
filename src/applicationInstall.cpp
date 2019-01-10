#include "applicationInstall.h"

ApplicationInstall::ApplicationInstall(const QDir &dir, Network *network) : AbstractApplication ()
{
    initPath(dir);
    AbstractApplication::initNet(network);

    if(!initConfig(appPath))
    {
        initNoConfig();
        if (net->isConnected())
        {
            requestConfigData(net);
        }
        else
        {
            QString errorStr("no init version, no net connect");
            throw Exception(12,errorStr);
        }
    }
    else
    {
        if (initConfig(appCfg))
        {
            initNoConfig();
        }
        if (!verCon->isFoundVersions())
        {
            QString errorStr("no init version, no found version");
            throw Exception(12,errorStr);
        }
    }
}

UiApplication *ApplicationInstall::getUiApplication()
{
    
}

bool ApplicationInstall::initUiApp()
{
    uiApp = new UiApplication (appName);
    //if  (actualVersion != NULL)
    {
        uiApp->setIcon(appIcon);
        /*QStringList supportLanguage = actualVersion->getSupportLanguage();
        uiApp->setSupportLanguage(&supportLanguage);
        QList<PlatformType> supportPlatform = actualVersion->getSupportPlatform();
        uiApp->setPlatforms(&supportPlatform);
        QString recSysReq = actualVersion->getRecommendedSystemRequirements();
        uiApp->setRecommendedSystemRequirements(&recSysReq);
        QString minSysReq = actualVersion->getMinimumSystemRequirements();
        uiApp->setMinimumSystemRequirements(&minSysReq);*/
        //uiApp->setVersionList(verCon->getFullListVersionStrList());
        //QString currenVer = actualVersion->getFullName();
        //uiApp->setCurrentVersion(&currenVer);
    }


    return true;
}

bool ApplicationInstall::initNoConfig()
{
    initNameFromFolder(appPath);
    return true;
}

bool ApplicationInstall::initConfig(Config *cfg)
{
    if (cfg->isEmpty()) return false;
    initNameFromConfig(cfg);
    initIcon(cfg);
    initId(cfg);
    initDateRelease(cfg);
    initDateLastUpdate(cfg);
    initVerCon(net,appPath,appName);
    return true;
}

bool ApplicationInstall::initPath(const QDir &path)
{
    if (!(path.exists()))
    {
        QString errorPath = "not found path application:";
        errorPath.append(path.absolutePath());
        throw Exception(13,errorPath);
    }
    appPath = new QDir (path);
    return true;
}

bool ApplicationInstall::initConfig(QDir *path)
{
    QString cfgPath = path->absolutePath();
    cfgPath.append("/");
    cfgPath.append(configFileName);

    appCfg = new Config (cfgPath);
    if (appCfg->isEmpty())
    {
        return false;
    }
    return true;
}

bool ApplicationInstall::initIcon(Config *cfg)
{
    QString cfgAppName = cfg->get(configKeyAppName).at(0);
    if (cfg->isError(cfgAppName)) return false;
    appName = new QString(cfgAppName);
    return true;
}

bool ApplicationInstall::initId(Config *cfg)
{
    appId = new short;
    QString id = cfg->get(configKeyAppId).at(0);
    if (cfg->isError(id)) return false;
    *appId = id.toShort();
    return true;
}

bool ApplicationInstall::initNameFromFolder(QDir *folder)
{
    if (folder->exists())
    {
        appName = new QString (folder->dirName());
        return true;
    }
    return false;
}

bool ApplicationInstall::initNameFromConfig(Config *cfg)
{
    QString cfgAppName = cfg->get(configKeyAppName).at(0);
    if (cfg->isError(cfgAppName)) return false;
    appName = new QString(cfgAppName);
    return true;
}

bool ApplicationInstall::initDateRelease(Config *cfg)
{
    QString cfgAppDate = cfg->get(configKeyAppCreated).at(0);
    if (cfg->isError(cfgAppDate)) return false;
    QStringList cfgAppDateList = cfgAppDate.split(",");
    if (cfgAppDateList.count() < 3) return false;
    appRelease = new QDate(cfgAppDateList.at(0).toInt(),
                           cfgAppDateList.at(1).toInt(),
                           cfgAppDateList.at(2).toInt());
    return true;
}

bool ApplicationInstall::initDateLastUpdate(Config *cfg)
{
    QString cfgAppDate = cfg->get(configKeyAppLastUpdate).at(0);
    if (cfg->isError(cfgAppDate)) return false;
    QStringList cfgAppDateList = cfgAppDate.split(",");
    if (cfgAppDateList.count() < 3) return false;
    appLastUpdate = new QDate(cfgAppDateList.at(0).toInt(),
                           cfgAppDateList.at(1).toInt(),
                           cfgAppDateList.at(2).toInt());
    return true;
}

bool ApplicationInstall::requestConfigData(Network *network)
{
    if (!(network->isConnected())) return false;
    AbstractRequest *reqAppInfo = network->getAppInfo(*appName);
    connect(reqAppInfo,&AbstractRequest::replyServer,this,&ApplicationInstall::reciveAppInfo);
    return true;
}

bool ApplicationInstall::fillingConfig(QMap<QString, QStringList> &data, Config *cfg)
{
    cfg->clear();
    foreach (QString key, data.keys())
    {
        cfg->set(key,data.value(key));
    }
    cfg->save();
    return true;
}

void ApplicationInstall::reciveAppInfo(QList<NetworkData> *response)
{
    QMap<QString, QStringList> data;
    foreach (NetworkData netData, *response)
    {
        QString key = netData.key;
        QVariant value = netData.value;
        data.insert(key,value.toStringList());
    }
    fillingConfig(data,appCfg);
    initConfig(appCfg);
}
