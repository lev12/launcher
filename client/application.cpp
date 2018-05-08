#include "application.h"

Application::Application(QString path, Network *network)
{
    initAppPath(path);
    initNet (network);
    initConfig ();
    initAppName();
    initVerCon ();

    verCon->setLastCurrentVesion(cfgApp->get("last_current_version").at(0));
}

bool Application::initNet(Network *network)
{
    if (network == NULL)
    {
        net = new Network ();
        return false;
    }
    net = network;
    return true;
}

bool Application::initAppName()
{
    QString *cfgAppName = new QString (cfgApp->get("name").at(0));
    if (*cfgAppName == cfgApp->errorResponse) return false;
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
    appPath = new QString (path);
    return true;
}

bool Application::initAppIcon()
{
    QString iconPath = cfgApp->get("iconPath").at(0);
    if (iconPath == cfgApp->errorResponse) return false;

    appIcon = new QIcon (iconPath);
    return true;
}

bool Application::initVerCon()
{
    if (net->isConnected() == false || *appPath == "" || *appName == "")
    {
        QString nullstring = "";
        verCon = new VersionController(&nullstring, net, &nullstring);
        return false;
    }

    verCon = new VersionController(appPath, net, appName);
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
        QList<Platform> supportPlatform = actualVersion->getSupportPlatform();
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

    QString cfgPath = *appPath;
    cfgPath.append("/");
    cfgPath.append("app");
    cfgPath.append(".cfg");

    cfgApp = new Config (cfgPath);
    if (cfgApp->isEmpty())
    {
        if (!(fillingConfigApp ()))
        {
            return false;
        }
    }
    return true;
}

bool Application::setLastCurrentVersionOfConfig(QString *verName)
{
    if (cfgApp == NULL) return false;
    cfgApp->set("last_current_version", *verName);
    cfgApp->save();

    return true;
}


UiApplication* Application::getUiApplication()
{
    if (uiApp == NULL) initUiApp();
    uiApp->setActivePage(1); //TODO read cfg
    return uiApp;
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
    //TODO
    return true;
}

QList<Platform> Application::strToPlatform (QStringList platformStrList)
{
    QList<Platform> resault;
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

