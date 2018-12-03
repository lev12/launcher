#ifndef ABSTRACTAPPLICATION_H
#define ABSTRACTAPPLICATION_H

#include <QObject>
#include <QString>
#include <QIcon>

#include "exception.h"
#include "globalVariable.h"
#include "network/network.h"
#include "versionController.h"
#include "ui/uiApplication.h"
#include "ui/uiApplicationItem.h"
#include "config.h"

class AbstractApplication : public QObject
{
    Q_OBJECT

public:
    AbstractApplication();

    virtual UiApplication* getUiApplication() = 0;
    UiApplicationItem* getUiApplicationItem();
    bool deleteUiApplication ();

    bool static checkApplication(QString AppPath);
    bool getIsInstall() const;

protected:

    VersionController *verCon;
    UiApplication *uiApp;
    Network *net;

    QString *appName;
    QIcon *appIcon;
    short *appId;
    QDate *appRelease;
    QDate *appLastUpdate;
    bool *isInstall;

    bool initVerCon (Network *network, QDir *path, QString *name);
    bool initNet (Network *network);
    bool initIsInstall (bool isInstall);
};

#endif // ABSTRACTAPPLICATION_H
