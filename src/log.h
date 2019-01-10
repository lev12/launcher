#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <QMap>
#include <QVector>
#include <QtAlgorithms>
#include <QHostAddress>
#include <QRegExp>

class Log
{
private:

    QFile *logFile;

    class Node
    {
    public:
        int n;
        char c;
        Node *left, *right;

        Node ();
        Node (Node *l, Node *r);
    };

    void buildTable(Node *root);
    QVector<bool> *code;
    QMap < char,QVector<bool> > *table;
    const QString defaultLogPath = ".\\log";
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
    void grabber (int countFileDelete);
    void addMessage (QString message);
    void end ();

    bool compression();
    bool compressionHaffman(QString pathInputFile, QString pathOutputFile);

    ~Log();
};

#endif // LOG_H
