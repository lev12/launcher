#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDir>
#include <QFile>

#include "ui/uiApplicationItem.h"
#include "network/network.h"
#include "abstractApplication.h"
#include "applicationInstall.h"
#include "applicationNoInstall.h"

/*!
 * This is a controller applications.
 * =================================
 *
 * This class working wiht network.
 * --------------------------------
 * - request application list
 *
 */

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    ApplicationController(const QString &pathToFolderWithApp, Network *network, QObject *parent = nullptr);

    QList <AbstractApplication*> getAppList ();
    QList <ApplicationInstall*> getAppInstallList ();
    QList <ApplicationNoInstall*> getAppNoInstallList ();
    
    QList <UiApplicationItem*> getAppItemList () const;
    QDir *getRootFolder () const;

    ~ApplicationController();
private:

    Network *net;
    QDir *folderWithApp;
    QList <AbstractApplication*> *appList;

    bool initNetwork (Network *network);
    bool initFolderWithVersion (const QString &pathToFolderWithApp);
    bool initAppList ();

    bool fillingAppListFromDrive (QDir *folder);
    bool fillingAppListFromNetwork (QStringList *app);
    bool requestAppList(Network *network);
private slots:
    void reciveAppList (QList<NetworkData> *response);
};

#endif // APPLICATIONCONTROLLER_H
