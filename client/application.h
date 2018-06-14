#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>

#include <QObject>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QProcess>
#include <QUrl>
#include <QDateTime>
#include <QDesktopServices>

#include "globalVariable.h"
#include "network/network.h"
#include "versionController.h"
#include "ui/uiapplication.h"
#include "config.h"

class Application : public QObject
{
    Q_OBJECT
public:
    Application(QString path, Network *network);

    UiApplication* getUiApplication();
    bool deleteUiApplication ();

    bool deleteAllVersion ();
    bool static checkApplication(QString AppPath);
private:

    VersionController *verCon;
    UiApplication *uiApp;
    Network *net;
    Config *cfgApp;
    QDir *appPath;


    //info app
    QString *appName;
    QIcon *appIcon;
    short *id;
    QDateTime *created;

    bool initAppPath (QString path);
    bool initVerCon (Network *network, QDir *path, QString *name);
    bool initNet (Network *network);
    bool initAppName (QDir *path);
    bool initAppNameConfig (Config *cfg);
    bool initAppIcon ();
    bool initUiApp ();
    bool initConfig ();
    bool initId (Config *cfg);

    bool setLastCurrentVersionOfConfig (QString *verName);
    bool fillingConfigApp();
    QList<Platform> strToPlatform (QStringList platformStrList);
private slots:
    void reciveAppInfo (QList<NetworkData> *response);
};

#endif // APPLICATION_H
