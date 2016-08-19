#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QHostAddress>

class Log
{
private:
    QFile *logFile;

public:
    Log(QString PathLog);
    void print (QString text);
};

#endif // LOG_H
