#include "application.h"
#include <QTime>

Application::Application(QString path, Network *network)
{
    verCon = NULL;
    uiApp = NULL;
    net = NULL;
    cfgApp = NULL;
    appName = NULL;
    appIcon  = NULL;
    appPath = NULL;
    appSupportLanguage = NULL;
    appSupportPlatform = NULL;
    appRecommendedSystemRequirements = NULL;
    appMinimumSystemRequirements = NULL;
    actualVersion = NULL;

    initAppPath(path);
    initNet (network);
    initConfig ();
    initAppName();
    initVerCon ();
    initSupportLanguage ();
    initSupportPlatform ();
    initSystemRequirements ();
    initActualVersion();
}

bool Application::initAppName()
{
    if (cfgApp == NULL) return false;

    appName = new QString (cfgApp->get("name").at(0));
    return true;
}

bool Application::initNet(Network *network)
{
    if (network == NULL) return false;

    net = network;
    return true;
}

bool Application::initAppPath(QString path)
{
    if (!(QFile::exists(path))) return false;

    appPath = new QString (path);

    return true;
}

bool Application::initAppIcon()
{
    if (cfgApp == NULL) return false;
    QString iconPath = cfgApp->get("iconPath").at(0);
    appIcon = new QIcon (iconPath);
    return true;
}

bool Application::initVerCon()
{
    if (net == NULL || appPath == NULL) return false;

    verCon = new VersionController(*appPath, net);
    return true;
}

bool Application::initUiApp()
{
    if (verCon == NULL) return false;
    uiApp = new UiApplication ();
    uiApp->initName(appName);
    uiApp->initSupportLanguage(appSupportLanguage);
    uiApp->initIcon(appIcon);
    uiApp->initPlatforms(appSupportPlatform);
    uiApp->initRecommendedSystemRequirements(appRecommendedSystemRequirements);
    uiApp->initMinimumSystemRequirements(appMinimumSystemRequirements);
    uiApp->initVersionList(verCon->getFullListVersionStrList());
    uiApp->setCurrentVersion(actualVersion);
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

bool Application::initSupportLanguage()
{
    if (cfgApp == NULL) return false;

    QList <QString> lang = cfgApp->get("languages");

    appSupportLanguage = new QStringList (lang);

    return true;
}

bool Application::initSupportPlatform()
{
    if (cfgApp == NULL) return false;

    QStringList platformList = cfgApp->get("platforms");
    appSupportPlatform = new QList<Platform> (strToPlatform(platformList));
    return true;
}

bool Application::initSystemRequirements()
{
    if (cfgApp == NULL) return false;

    QString recSysReq = cfgApp->get("RecommendedSystemRequirements").at(0);
    QString minSysReq = cfgApp->get("MinimumSystemRequirements").at(0);
    if (recSysReq == "false" || minSysReq == "false")
    {
        if  (!(fillingConfigApp ()))
        {
            // TODO create error signal
            qDebug () << "application error filling config in sys req";
        }
    }
    appRecommendedSystemRequirements = new QString(recSysReq);
    appMinimumSystemRequirements = new QString (minSysReq);

    return true;
}

bool Application::initActualVersion()
{
    actualVersion = new QString ("alpha_45");
    return true;
}

UiApplication* Application::getUiApplication()
{
    if (uiApp == NULL) initUiApp();
    uiApp->setActivePage(1); //TODO read cfg
    return uiApp;
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

