#ifndef APPLICATIONNOINSTALL_H
#define APPLICATIONNOINSTALL_H

#include "abstractApplication.h"
#include "cacheOnDirve.h"

class ApplicationNoInstall : public AbstractApplication
{
    Q_OBJECT

public:
    ApplicationNoInstall(const QString &AppName, Network *network);

    virtual UiApplication* getUiApplication();

private:
    QString iconFileName = "favicon.ico";

    CacheOnDirve *cacheDirve;
    int *sectorIndex;

    bool initName (const QString &name);
    bool initIcon (const QString &path);
    bool initIcon (const QFile &path);
    bool initId (const short &id);
    bool initDateRelease (const QDate &date);
    bool initDateLastUpdate (const QDate &date);
    bool initCacheFolder(const short &id);
    bool initSectorIndex(const short &id);

    bool requestAppData (Network *network);
    bool requestAppIcon (Network *network, QUrl &url);
private slots:
    void reciveAppInfo(QList<NetworkData> *response);
    void reciveAppIcon(QList<NetworkData> *response);
};

#endif // APPLICATIONNOINSTALL_H
