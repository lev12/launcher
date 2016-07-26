#ifndef VERSIONS_H
#define VERSIONS_H

#include <QList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTcpSocket>
#include <QComboBox>
#include <QTextStream>
#include <QObject>
#include <QRegExp>

#include "global_variable.h"

class versions : public QObject
{
    Q_OBJECT

private:
    int removeFolder(QDir & dir);

    enum type_ver
    {
        pre_alpha,
        alpha,
        beta,
        release,
    };

    struct ver
    {
        QString name;
        bool install;
    };

private slots:
    void readServer();

public:
    versions(QComboBox *cb);

    QDir dir;
    QFile file;

    QList <ver> versions_all;
    QStringList versions_net;
    QList <QFileInfo> versions_bin;

    QComboBox *g_cb;
    QTcpSocket *client;

    void init();
    bool addVersion(QString type,QString number);
    bool deleteVersion(QString type,QString number);
    bool checkVersion(QString type, QString number);
    bool checkVersion(QFileInfo path);
    QFileInfo getFile (QString type, QString number);
    bool open();
    void FillingComboBox (QComboBox *cb);
    QString getVersionName (QFileInfo path);
    QString getExeFile (QFileInfo path);
    QString getItemComboBox (QComboBox *cb);

    bool getVersionListOnServer (QTcpSocket *client);
    bool connectNet (QTcpSocket *client);

    bool parse (QString data, QTcpSocket *client);
    bool parseConnectServer (QString data, QTcpSocket *client);
    bool parseListVersions (QString data,QTcpSocket *client);
};

#endif // VERSIONS_H
