#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDir>
#include <QList>
#include <QTextStream>

class File
{
private:
    QList<QFileInfo> versions;
public:
    File();
    void FillingVersionList ();
    bool checkVersion(QFileInfo path);
    QFileInfo getFile (QString type, QString number);
    QList<QFileInfo> getVersonsList();
};

#endif // FILE_H
