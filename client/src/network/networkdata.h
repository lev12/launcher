#ifndef NETWORKDATA_H
#define NETWORKDATA_H
#include <QString>
#include <QVariant>

struct NetworkData
{
    QString key;
    QVariant value;
};
Q_DECLARE_METATYPE(NetworkData)

#endif // NETWORKDATA_H
