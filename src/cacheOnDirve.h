#ifndef CACHEONDRIVE_H
#define CACHEONDRIVE_H

#include <QObject>
#include <QDir>
#include <QCryptographicHash>
#include <QMap>
#include "Exception.h"

class CacheOnDirve : public QObject
{
    Q_OBJECT
public:
    explicit CacheOnDirve(QDir &path,QObject *parent = nullptr);

    bool addSector (int &sector);
    QFile* addFile (int &sector,QString &key);

    QFile* value (int &sector,QString &key);
    bool isExistsKey(int &sector,QString &key);
private:
    QDir *dirCache;
    QMap <QByteArray,QStringList> *metaCache;
    
    bool isSector ();
    QList <QDir*> *sectorList;
};

#endif // CACHEONDRIVE_H
