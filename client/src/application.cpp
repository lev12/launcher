#include "application.h"

Application::Application(QString path, Network *network)
{
    uiApp = NULL;

    initAppPath(path);
    initNet (network);
    initAppName (appPath);
    if (!initConfig ())
    {
        fillingConfigApp ();
    }
    else
    {
        initAppNameConfig(appCfg);
        initId (appCfg);
        initVerCon (net, appPath, appName);

        verCon->setLastCurrentVesion(appCfg->get("last_current_version").at(0));
    }
}

bool Application::initNet(Network *network)
{
    if (network == NULL)
    {
        net = new Network (cfgLauncher.get("DomainServer").at(0),QString(cfgLauncher.get("PortServer").at(0)).toUShort());
        return false;
    }
    net = network;
    return true;
}

bool Application::initAppName(QDir *path)
{
    if (path->exists())
    {
        appName = new QString (path->dirName());
        return true;
    }
    return false;
}

bool Application::initAppNameConfig(Config *cfg)
{
    QString *cfgAppName = new QString (cfg->get("name").at(0));
    if (*cfgAppName == cfg->errorResponse) return false;
    appName = cfgAppName;
    return true;
}

bool Application::initAppPath(QString path)
{
    if (!(QFile::exists(path)))
    {
        QString errorPath = "not found path application:";
        errorPath.append(path);
        throw errorPath;
        return false;
    }
    appPath = new QDir (path);
    return true;
}

bool Application::initAppIcon()
{
    QString iconPath = appCfg->get("iconPath").at(0);
    if (iconPath == appCfg->errorResponse) return false;

    appIcon = new QIcon (iconPath);
    return true;
}

bool Application::initVerCon(Network *network, QDir *path, QString *name)
{
    QString *appDirStr = new QString(path->absolutePath());
    //verCon = new VersionController(appDirStr, network, name);
    return true;
}

bool Application::initUiApp()
{
    if (verCon == NULL) return false;
    uiApp = new UiApplication (NULL, appName);
    Version *actualVersion = verCon->getLsatCurrentVersion();
    if  (actualVersion != NULL)
    {
        uiApp->setIcon(appIcon);
        QStringList supportLanguage = actualVersion->getSupportLanguage();
        uiApp->setSupportLanguage(&supportLanguage);
        QList<PlatformType> supportPlatform = actualVersion->getSupportPlatform();
        uiApp->setPlatforms(&supportPlatform);
        QString recSysReq = actualVersion->getRecommendedSystemRequirements();
        uiApp->setRecommendedSystemRequirements(&recSysReq);
        QString minSysReq = actualVersion->getMinimumSystemRequirements();
        uiApp->setMinimumSystemRequirements(&minSysReq);
        uiApp->setVersionList(verCon->getFullListVersionStrList());
        QString currenVer = actualVersion->getFullName();
        uiApp->setCurrentVersion(&currenVer);
    }


    return true;
}

bool Application::initConfig()
{
    if (appPath == NULL)
    {
        return false;
    }

    QString cfgPath = appPath->absolutePath();
    cfgPath.append("/");
    cfgPath.append("app");
    cfgPath.append(".cfg");

    appCfg = new Config (cfgPath);
    if (appCfg->isEmpty())
    {
        return false;
    }
    return true;
}

bool Application::initId(Config *cfg)
{
    appId = new short;
    QString idstr = cfg->get("id").at(0);
    if (idstr != cfg->errorResponse)
    {
        *appId = idstr.toShort();
        return true;
    }
    return false;
}

bool Application::setLastCurrentVersionOfConfig(QString *verName)
{
    if (appCfg == NULL) return false;
    appCfg->set("last_current_version", *verName);
    appCfg->save();

    return true;
}


UiApplication* Application::getUiApplication()
{
    if (uiApp == NULL) initUiApp();
    uiApp->setActivePage(1); //TODO read cfg
    return uiApp;
}

uiApplicationItem* Application::getUiApplicationItem()
{

}

bool Application::deleteUiApplication()
{
    if (uiApp != NULL) return false;
    setLastCurrentVersionOfConfig (uiApp->getCurrentVersion());
    delete uiApp;
    return true;
}

bool Application::deleteAllVersion()
{
    if (verCon == NULL) return false;

    verCon->deleteAllVersion();

    return true;
}

bool Application::fillingConfigApp()
{
    if (net == NULL) return false;
    if (!(net->isConnected())) return false;
    AbstractRequest *reqAppInfo = net->getAppInfo(*appName);
    connect(reqAppInfo,AbstractRequest::replyServer,this,Application::reciveAppInfo);
    return true;
}

void Application::reciveAppInfo(QList<NetworkData> *response)
{
    appCfg->clear();
    foreach (NetworkData data, *response)
    {
        QString key = data.key;
        QString value = data.value;
        appCfg->set(key,value);
    }
    appCfg->save();
}

QList<PlatformType> Application::strToPlatform(QStringList platformStrList)
{
    QList<PlatformType> resault;
    foreach (QString tempList, platformStrList)
    {
        if (tempList == "PC") resault << PC;
        else if (tempList == "MAC") resault << MAC;
        else if (tempList == "Android") resault << Android;
        else if (tempList == "IOS") resault << IOS;
        else if (tempList == "XBox") resault << XBox;
        else if (tempList == "PlayStation") resault << PlayStation;
    }
    return resault;
}



bool Application::checkApplication(QString AppPath)
{
    QString pathToConfig = AppPath;
    pathToConfig.append("/app.cfg");
    if (!(QFile::exists(pathToConfig)))
    {
        return false;
    }

    Config appConfig(pathToConfig);
    QString AppName = appConfig.get("name").at(0);
    if (AppName == appConfig.errorResponse)
    {
        return false;
    }

    //VersionController versionController(&AppPath, NULL, &AppName);
    /*if (!(versionController.isFoundVersions()))
    {
        return false;
    }*/

    return true;
}
