#ifndef ABSTRACTVERSION_H
#define ABSTRACTVERSION_H

#include <QObject>
#include "network/network.h"
#include "versionType.h"
#include "platformType.h"
#include <exception>

class AbstractVersion : public QObject
{
    Q_OBJECT
public:
    AbstractVersion();

    QString getFullName ();
    int getVersionNumber ();
    VersionType getVersionType ();
    bool getIsInstall ();
    QString getAppName ();

    static QString versionTypeToString (VersionType type);
    static VersionType stringToVersionType (QString str);
    static PlatformType stringToPlatform(QString platformStr);
protected:
    QString *appName;
    int *verNumber;
    VersionType *verType;
    bool *verIsInstall;

    void initIsInatall (bool install);
    void initAppName (QString AppName);
    bool initVerName (QString VerName);
};

#endif // ABSTRACTVERSION_H
