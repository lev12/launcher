#include "applicationcontroller.h"

ApplicationController::ApplicationController(QString pathToFolderWithApp, Network *network)
{
    net = NULL;
    folderWithApp = NULL;
    appList = NULL;

    initNetwork (network);
    initFolderWithVersion (pathToFolderWithApp);
    initAppList ();
}

ApplicationController::~ApplicationController()
{

}

bool ApplicationController::initNetwork(Network *network)
{
    net = network;
    return true;
}

bool ApplicationController::initFolderWithVersion(QString pathToFolderWithApp)
{
    folderWithApp = new QDir (pathToFolderWithApp);
    if (!(folderWithApp->exists()))
    {
        delete folderWithApp;
        folderWithApp = NULL;
        return false;
    }
    return true;
}

bool ApplicationController::initAppList()
{
    appList = new QList <Application*> ();
    fillingAppList ();
    return true;
}

bool ApplicationController::fillingAppList()
{
    if (appList == NULL) return false;

    QFileInfoList appDirList = folderWithApp->entryInfoList();
    foreach (QFileInfo tempFileInfo, appDirList)
    {
        QString tempPath = tempFileInfo.absoluteFilePath();
        if (checkApplication(tempPath))
        {
            Application *app = new Application (tempPath, net);
            appList->operator <<(app);
        }
    }

    return true;
}

bool ApplicationController::checkApplication(QString pathToFolder)
{
    QString pathToConfig = pathToFolder;
    pathToConfig.append("/app.cfg");
    if (!(QFile::exists(pathToConfig))) return false;
    else return true;
}

QList <Application *> *ApplicationController::getAppList()
{
    if (appList == NULL) initAppList();
    return appList;
}

QDir *ApplicationController::getRootFolder()
{
    if (folderWithApp == NULL) return NULL;
    return folderWithApp;
}
