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

/*class Node : public QObject
{
    Q_OBJECT
public:
    int n;
    char c;
    Node *left, *right;

    Node ();
    Node (Node *l, Node *r);
};*/

class Log : public QObject
{
    Q_OBJECT
private:

    QFile *logFile;



    //void buildTable(Node *root);
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
    Q_ENUM (type)

    enum state
    {
        noLogging,
        logging,
        loggingAndSend
    };
    Q_ENUM (state)


    Log(QDir PathLog);

    void head ();
    void print (QString text = "Null", type classMessages = info);
    void grabber (unsigned int countFileDelete);
    void addMessage (QString message);
    void end ();

    //bool compression();
    //bool compressionHaffman(QString pathInputFile, QString pathOutputFile);

    ~Log();
};

#endif // LOG_H
