#include "applicationController.h"

/*! @fn ApplicationController::ApplicationController(const QString &pathToFolderWithApp, Network *network, QObject *parent)
 * @brief Constructor wiht full init
 * @param pathToFolderWithApp path to the folder where the application is stored
 * @param network api launcher
 * @param parent set parent object
 */
ApplicationController::ApplicationController(const QString &pathToFolderWithApp, Network *network, QObject *parent) :
    QObject(parent)
{
    initNetwork (network);
    initFolderWithVersion (pathToFolderWithApp);
    initAppList ();
    if (net->isConnected())
    {

    }
    fillingAppListFromDrive(folderWithApp);
}

/*! @fn ApplicationController::~ApplicationController()
 * @brief Destroed this object
 */
ApplicationController::~ApplicationController()
{
    delete folderWithApp;
    foreach (AbstractApplication *app, *appList)
    {
        delete app;
    }
    delete appList;
}

bool ApplicationController::initNetwork(Network *network)
{
    net = network;
    return true;
}

bool ApplicationController::initFolderWithVersion(const QString &pathToFolderWithApp)
{
    folderWithApp = new QDir (pathToFolderWithApp);
    if (!(folderWithApp->exists()))
    {
        delete folderWithApp;
        folderWithApp = nullptr;
        return false;
    }
    return true;
}

bool ApplicationController::initAppList()
{
    appList = new QList <AbstractApplication*> ();
    return true;
}

bool ApplicationController::fillingAppListFromDrive(QDir *folder)
{
    QFileInfoList appDirList = folder->entryInfoList();
    foreach (QFileInfo tempFileInfo, appDirList)
    {
        QString tempAppPath = tempFileInfo.absoluteFilePath();

        if (AbstractApplication::checkApplication(tempAppPath))
        {
            AbstractApplication *app = new ApplicationInstall (tempAppPath, net);
            appList->operator <<(app);
        }
    }

    return true;
}

bool ApplicationController::fillingAppListFromNetwork(QStringList *app)
{
    foreach (AbstractApplication *item,*appList)
    {
        if (item->getIsInstall() == false)
        {
            appList->removeOne(item);
            delete item;
        }
    }
    foreach (QString appItem, *app)
    {
        AbstractApplication *appInstall = new ApplicationNoInstall (appItem, net);
        appList->operator <<(appInstall);
    }
    return true;
}

bool ApplicationController::requestAppList(Network *network)
{
    if (!(network->isConnected())) return false;
    AbstractRequest *reqAppList = network->getApplicationList();
    connect(reqAppList,&AbstractRequest::replyServer,this,&ApplicationController::reciveAppList);
    return true;
}

void ApplicationController::reciveAppList(QList<NetworkData> *response)
{
    QStringList netAppList;
    foreach (NetworkData netData, *response)
    {
        netAppList << netData.value.toString();
    }
    fillingAppListFromNetwork(&netAppList);
}

/*! @fn QList<ApplicationInstall *> ApplicationController::getAppInstallList()
 *  @brief filling application list from drive and network
 *  @return list wiht pointer on ApplicationInstall else return empty list
 */
QList<AbstractApplication *> ApplicationController::getAppList()
{
    return *appList;
}

/*! @fn QList<ApplicationInstall *> ApplicationController::getAppInstallList()
 *  @brief filling application list from drive
 *  @return list wiht pointer on ApplicationInstall else return empty list
 */
QList<ApplicationInstall *> ApplicationController::getAppInstallList()
{
    QList<ApplicationInstall *> appInstallList;
    foreach (AbstractApplication *appItem, *appList)
    {
        if (appItem->getIsInstall() == true)
        {
            appInstallList.operator<<(static_cast<ApplicationInstall*>(appItem));
        }
    }
    return appInstallList;
}

/*! @fn QList<ApplicationNoInstall *> ApplicationController::getAppNoInstallList()
 *  @brief filling application list from network
 *  @return list wiht pointer on ApplicationNoInstall else return empty list
 */
QList<ApplicationNoInstall *> ApplicationController::getAppNoInstallList()
{
    QList<ApplicationNoInstall *> appNoInstallList;
    foreach (AbstractApplication *appItem, *appList)
    {
        if (appItem->getIsInstall() == false)
        {
            appNoInstallList.operator<<(static_cast<ApplicationNoInstall*>(appItem));
        }
    }
    return appNoInstallList;
}

/*! @fn QList<UiApplicationItem *> ApplicationController::getAppItemList() const
 *  @brief filling item application list from application list
 *  @return list wiht pointer on UiApplicationItem else return empty list
 */
QList<UiApplicationItem *> ApplicationController::getAppItemList() const
{
    QList <UiApplicationItem*> resault;
    foreach (AbstractApplication *item, *appList)
    {
        resault << item->getUiApplicationItem();
    }
    return  resault;
}

/*! @fn QDir *ApplicationController::getRootFolder() const
 *  @brief folder with applacations
 *  @return list wiht pointer on UiApplicationItem else return null pointer
 */
QDir *ApplicationController::getRootFolder() const
{
    return folderWithApp;
}
