#ifndef PLATFORMTYPE_H
#define PLATFORMTYPE_H

#include <QMetaType>

enum PlatformType
{
    PC,
    MAC,
    Android,
    IOS,
    XBox,
    PlayStation,
    Null
};

Q_DECLARE_METATYPE (PlatformType)
#endif // PLATFORMTYPE_H
