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

    QString *appName;
    QIcon *appIcon;
    QString *appPath;


    bool initAppPath (QString path);
    bool initVerCon ();
    bool initNet (Network *network);
    bool initAppName ();
    bool initAppIcon ();
    bool initUiApp ();
    bool initConfig ();

    bool setLastCurrentVersionOfConfig (QString *verName);
    bool fillingConfigApp();
    QList<Platform> strToPlatform (QStringList platformStrList);
};

#endif // APPLICATION_H
