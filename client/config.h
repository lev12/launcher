#ifndef CONFIG_H
#define CONFIG_H

#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QDebug>
#include <qmath.h>

class Config
{
private:
    bool empty;
    int countLine = 10;
    QFile *configFile;

public:

    QStringList *configKeyName;
    QStringList *configKeyValue;

    Config(QString path = ".\\conf.cfg");
    ~Config();
    bool create(QString path);
    bool raedFile();
    bool save ();
    QStringList get(QString parametr);
    bool set(QString parametr, QString value);
    bool isEmpty ();
};

#endif // CONFIG_H
