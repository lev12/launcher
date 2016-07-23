#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDir>
#include <QList>
#include <QTextStream>

class File
{
private:

public:
    QList<QFileInfo> versions;

    File();
    void FillingVersionList ();
    bool checkVersion(QFileInfo path);
    QFileInfo getFile (QString type, QString number);
    QList<QFileInfo> getVersonsList();
    QString getVersionName (QFileInfo path);
};

#endif // FILE_H
