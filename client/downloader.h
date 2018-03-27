#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QString>
#include <QList>
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QString AppName,  QObject *parent);
    ~Downloader();

    bool requestActualVersion();
    bool requestVersionList();
    bool requestCheckVersion();
    bool requestExeFileVersion();
    bool requestFileListVersion();
    bool requestSizeVersion();
    bool requestFileSize();
    bool requestApplicationInfo();

private:
    enum DownloadType
    {
        ActualVersion,
        VersionList,
        CheckVersion,
        ExeFileVersion,
        FileListVersion,
        SizeVersion,
        FileSize,
        ApplicationInfo
    };

    QNetworkAccessManager *manager;
    QStringList *response;
    const QString apiHost = "http://electrical-simulator.ru/api/method/";
    QString appName;
    DownloadType downloaderType;

    QString _toSpace (QString str);
    QString spaceTo_ (QString str);
    QString deleteForRx (QString data);
    bool sendRequest (QString url_str);

    bool parseActualVersion   (QByteArray data);
    bool parseVersionList     (QByteArray data);
    bool parseCheckVersion    (QByteArray data);
    bool parseExeFileVersion  (QByteArray data);
    bool parseFileListVersion (QByteArray data);
    bool parseSizeVersion     (QByteArray data);
    bool parseFileSize        (QByteArray data);
    bool parseApplicationInfo (QByteArray data);
private slots:
    void readServer(QNetworkReply *reply);
signals:
    void replyServer (QStringList *response);
};

#endif // DOWNLOADER_H
