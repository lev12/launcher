#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <QHostAddress>
#include <QRegExp>

class Log : public QObject
{
    Q_OBJECT

signals:
    void comressionEnd(QString path);

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
    bool compressionHaffman(QString pathInputFile, QString pathOutputFile);
};

class Node
{
public:

};

#endif // LOG_H
