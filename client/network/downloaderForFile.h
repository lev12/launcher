#ifndef DOWNLOADERFORFILE_H
#define DOWNLOADERFORFILE_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QList>
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class DownloaderForFile : public QObject
{
    Q_OBJECT
public:
    DownloaderForFile(QUrl UrlFile, QFileInfo file, QObject *parent);
    ~DownloaderForFile();

    bool startDownloading();
    //bool pauseDownloading();
    bool cancelDownloading();

private:
    QUrl *urlFile;
    QFileInfo *saveFile;
    QFile *downloadingFile;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    bool initUrlFile(QUrl url);
    bool initSaveFile(QFileInfo file);
private slots:
    void finishedDownload();
    void readyReadDownload();

signals:
    void fileDownloaded(QStringList *response);
};

#endif // DOWNLOADERFORFILE_H
