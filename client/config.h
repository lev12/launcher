#ifndef CONFIG_H
#define CONFIG_H

#include <QTextStream>
#include <QFile>
#include <QList>
#include <qmath.h>

class config
{
private:
    void setDefaltParametr();
public:

    QStringList *name;
    QStringList *argumet;

    config();
    ~config();
    bool create();
    bool raedFile();
    bool save ();
    QString get(QString parametr);
    bool set(QString parametr, QString value);
};

#endif // CONFIG_H
