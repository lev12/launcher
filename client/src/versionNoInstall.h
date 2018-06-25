#ifndef VERSIONNOINSTALL_H
#define VERSIONNOINSTALL_H

#include "abstractVersion.h"

class VersionNoInstall : public AbstractVersion
{
public:
    VersionNoInstall(QString AppName, QString VerName);
};

#endif // VERSIONNOINSTALL_H
