#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QHostAddress>

class log
{
private:
    QFile *logFile;

public:
    log(QString PathLog);
    void print (QString text);
};

#endif // LOG_H
