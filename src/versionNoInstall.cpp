#include "versionNoInstall.h"

VersionNoInstall::VersionNoInstall(QString AppName, QString VerName) : AbstractVersion ()
{
    initIsInatall(false);
    initAppName(AppName);
    if(!initVerName(VerName))
    {
        throw "no correct ver name";
    }
}
