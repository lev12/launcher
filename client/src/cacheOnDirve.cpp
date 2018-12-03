#include "cacheOnDirve.h"

CacheOnDirve::CacheOnDirve(QDir &path,QObject *parent) : QObject(parent)
{
    dirCache = new QDir (path);
    metaCache = new QMap<QByteArray,QStringList> ();
    sectorList = new QList <QDir*> ();
}

bool CacheOnDirve::addSector(int &sector)
{
    QByteArray sectorHash = QCryptographicHash::hash(QByteArray::number(sector),QCryptographicHash::Sha1);
    if (!dirCache->mkdir(sectorHash)) return false;
    QDir *sectorDir = new QDir(dirCache->absoluteFilePath(QString(sectorHash)));
    sectorList->operator<<(sectorDir);
    return true;
}

QFile *CacheOnDirve::addFile(int &sector, QString &key)
{
    QByteArray sectorHash = QCryptographicHash::hash(QByteArray::number(sector),QCryptographicHash::Sha1);
    QStringList keyList (metaCache->value(sectorHash));
    keyList << key;
    metaCache->insert(sectorHash,keyList);
    QFile *file = new QFile (dirCache->absoluteFilePath(
                             sectorHash.append("/").append(key)));
    file->open(QFile::ReadOnly);
    file->close();
    return file;
}

QFile *CacheOnDirve::value(int &sector, QString &key)
{
    QByteArray sectorHash = QCryptographicHash::hash(QByteArray::number(sector),QCryptographicHash::Sha1);
    QString filePath (dirCache->absolutePath());
    filePath.append(sectorHash);
    filePath.append("/");
    filePath.append(key);

    QFile *file = new QFile (filePath);
    if (file->exists())
    {
        QString errorStr = "not found in cache on dirve file of path:";
        errorStr.append(filePath);
        Exception (5000,errorStr);
    }
    return file;
}

bool CacheOnDirve::isExistsKey(int &sector, QString &key)
{
    QStringList keyList = metaCache->value(QCryptographicHash::hash
                                           (QByteArray::number(sector),QCryptographicHash::Sha1),
                                           QStringList("no found value"));
    if(keyList == QStringList("no found value") || keyList.indexOf(key) != -1)
    {
        return false;
    }
    return true;
}
