#ifndef DOWNLOADERFORVERSION_H
#define DOWNLOADERFORVERSION_H

#include <QString>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QStorageInfo>
#include <QUrl>

#include "downloader.h"
#include "downloaderForFile.h"
#include "globalVariable.h"

class DownloaderForVersion : public QObject
{
    Q_OBJECT
public:
    DownloaderForVersion(QString AppName, QString VerName, QObject *parent);
    ~DownloaderForVersion();

    bool download();

private:

    bool getCheckVersion();
    bool getSizeVersion();
    bool getExeFile();
    bool getFileList();
    bool getFile(QUrl urlfile, QFileInfo file);

    bool checkDownload();
    bool downloadNextFile();
    bool checkFreeStorage();

    QStringList *responseVer;
    QString *appName;
    QString *verName;
    bool isVersion;
    int verSize;
    QString *exePath;
    QStringList *fileListVersion;
    int currentDonloadFile;
    QDir *verDir;
    const QString AdderssServer = "http://electrical-simulator.ru/api/method/";

private slots:
    void replyCheckVersion(QStringList *response);
    void replySizeVersion(QStringList *response);
    void replyExeFile(QStringList *response);
    void replyFileList(QStringList *response);
    void replyFile(QStringList *response);

signals:
    void complitDownload (QStringList *response);
    void error (int id);
};

#endif // DOWNLOADERFORVERSION_H
