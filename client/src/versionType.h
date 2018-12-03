#ifndef VERSIONTYPE_H
#define VERSIONTYPE_H

#include <QMetaType>

enum VersionType
{
    pre_alpha,
    alpha,
    beta,
    release,
    null
};

Q_DECLARE_METATYPE(VersionType)
#endif // VERSIONTYPE_H
