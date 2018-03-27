#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDir>
#include <QFile>

#include "application.h"
#include "network.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    ApplicationController(QString pathToFolderWithApp, Network *network);

    QList <Application*> *getAppList ();
    QDir *getRootFolder ();

    ~ApplicationController();
private:

    Network *net;
    QDir *folderWithApp;
    QList <Application*> *appList;

    bool initNetwork (Network *network);
    bool initFolderWithVersion (QString pathToFolderWithApp);
    bool initAppList ();

    bool fillingAppList ();
    bool checkApplication (QString pathToFolder);
};

#endif // APPLICATIONCONTROLLER_H
