#ifndef APPLICATIONINSTALL_H
#define APPLICATIONINSTALL_H

#include <QMap>

#include "abstractApplication.h"

class ApplicationInstall : public AbstractApplication
{
    Q_OBJECT

public:
    ApplicationInstall(const QDir &dir, Network *network);

    virtual UiApplication* getUiApplication();

private:
    const QString configFileName = "app.cfg";

    const QString configKeyAppName = "Name";
    const QString configKeyAppIcon = "IconPath";
    const QString configKeyAppId = "Id";
    const QString configKeyAppCreated = "DateRelease";
    const QString configKeyAppLastUpdate = "DataLastUpdete";

    QDir *appPath;
    Config *appCfg;

    bool initUiApp ();

    bool initNoConfig();
    bool initConfig(Config *cfg);

    bool initPath(const QDir &path);
    bool initConfig(QDir *path);
    bool initIcon (Config *cfg);
    bool initId (Config *cfg);
    bool initNameFromFolder(QDir *folder);
    bool initNameFromConfig(Config *cfg);
    bool initDateRelease (Config *cfg);
    bool initDateLastUpdate (Config *cfg);

    bool requestConfigData (Network *network);
    bool fillingConfig(QMap<QString, QStringList> &data, Config *cfg);

private slots:
    void reciveAppInfo (QList<NetworkData> *response);
};

#endif // APPLICATIONINSTALL_H
