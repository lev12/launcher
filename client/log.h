#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <QHostAddress>
#include <QRegExp>

class Log
{
private:
    QFile *logFile;

public:
    enum type
    {
        info,
        warning,
        error,
        critical_error
    };

    enum transfer
    {
        clientOut,
        sreverIn,
        null
    };

    Log(QString PathLog);

    void head ();
    void print (QString text = "Null", type classMessages = info, transfer InOut = null);
    void end ();

    bool compression();
};

#endif // LOG_H
