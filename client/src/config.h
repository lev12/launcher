#ifndef CONFIG_H
#define CONFIG_H

#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QDebug>
#include <qmath.h>

class Config
{
private:
    int countLine = 10;
    QFile *configFile;


public:
    static const QString errorResponse;
    QStringList *configKeyName;
    QStringList *configKeyValue;

    Config(QString path);
    ~Config();
    bool create(QString path);
    bool raedFile();
    bool save ();
    QStringList get(QString parametr);
    bool set(QString parametr, QString value);
    bool set(QString parametr, QStringList value);
    bool isEmpty ();
    void clear ();

    static bool isError (QString &value);
    QStringList &getConfigKeyName() const;
};
#endif // CONFIG_H
