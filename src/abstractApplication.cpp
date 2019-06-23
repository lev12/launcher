#include "abstractApplication.h"

AbstractApplication::AbstractApplication() : QObject ()
{

}

UiApplicationItem *AbstractApplication::getUiApplicationItem()
{
    return new UiApplicationItem (*appName,*appIcon);
}

bool AbstractApplication::deleteUiApplication()
{
    delete uiApp;
    return true;
}

bool AbstractApplication::checkApplication(QString AppPath)
{
    QString pathToConfig = AppPath;
    pathToConfig.append("/app.cfg");
    if (!(QFile::exists(pathToConfig)))
    {
        return false;
    }

    Config appConfig(pathToConfig);
    QString AppName = appConfig.get("Name").at(0);
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

bool AbstractApplication::getIsInstall() const
{
    return *isInstall;
}

bool AbstractApplication::initVerCon(Network *network, QDir *path, QString *name)
{
    verCon = new VersionController (*path, *network,*name);
    return true;
}

bool AbstractApplication::initNet(Network *network)
{
    net = network;
    return true;
}
