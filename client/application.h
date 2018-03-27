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
#include "network.h"
#include "versionController.h"
#include "uiapplication.h"
#include "config.h"

class Application : public QObject
{
    Q_OBJECT
public:
    Application(QString path, Network *network);

    UiApplication* getUiApplication();

    bool deleteAllVersion ();

private:

    VersionController *verCon;
    UiApplication *uiApp;
    Network *net;
    Config *cfgApp;

    QString *appName;
    QIcon *appIcon;
    QString *appPath;
    QStringList *appSupportLanguage;
    QList <Platform> *appSupportPlatform;
    QString *appRecommendedSystemRequirements;
    QString *appMinimumSystemRequirements;
    QString *actualVersion;

    bool initAppPath (QString path);
    bool initVerCon ();
    bool initNet (Network *network);
    bool initAppName ();
    bool initAppIcon ();
    bool initUiApp ();
    bool initConfig ();
    bool initSupportLanguage ();
    bool initSupportPlatform ();
    bool initSystemRequirements ();
    bool initActualVersion ();

    bool fillingConfigApp();
    QList<Platform> strToPlatform (QStringList platformStrList);
    /*appInfo app;
    QComboBox *comboBox;
    QPushButton *startButton;
    QHBoxLayout *pbHb;
    QProgressBar *progressBar;
    Network *network;
    VersionManager *versionmanager;
    VersionController *verContaoller;

    bool showVersionManager;
    QHBoxLayout *VMHB;

    QStringList versionsNetwork;

    QStringList sortVersions (QStringList versions);
public slots:
    void connectServer ();
    void listVersion ();
    void endDownloadFile ();
    void open();
    void updateButton();
    void updateDownload();
    void removeVersionManager();
    void deleteVersionVersionManager();
    void downloadVersionVersionManager();

signals:
    void getListVersions ();
    void downloadVersion ();

    void activeButton();
    void deactiveButton();*/
};

#endif // APPLICATION_H
