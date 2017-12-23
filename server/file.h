#ifndef FILE_H
#define FILE_H

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QList>
#include <QTextStream>

class File
{
private:
    QString nameApp;

public:
    QList<QFileInfo> versions;
    QDir *dirVer;


    File(QString AppName = NULL);
    void FillingVersionList ();
    bool checkVersion(QFileInfo path);
    bool checkVersion(QString type, QString number);
    QFileInfo getFile (QString type, QString number);
    QList<QFileInfo> getVersonsList();
    QString getVersionName (QFileInfo path);
    QString getExeFile (QFileInfo path);
    QString getAppName () const;
};

#endif // FILE_H
