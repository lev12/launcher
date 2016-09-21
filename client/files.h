#ifndef FILES_H
#define FILES_H

#include <QObject>
#include <QDebug>
#include <QTextStream>

#include <QFile>
#include <QDir>
#include <QFrame>

#include <QList>
#include <QString>

#include "global_variable.h"

class Files : public QFrame
{
private:

    QString folderName;
    int removeFolder(QDir & dir);

public:
    Files();

    void initFiles (QString FolderName);
    bool deleteVersion  (QString type, QString number);
    bool checkVersion   (QString type, QString number);
    bool checkVersion   (QFileInfo path);
    QFileInfo getFile   (QString type, QString number);
    bool isInstall      (QString type, QString number);
    QString getVersionName  (QFileInfo path);
    QString getExeFile      (QFileInfo path);
    void refreshFiles ();

protected:

    QList <QFileInfo> versionsInstalled;

};

#endif // FILES_H
