#include "downloaderForFile.h"

DownloaderForFile::DownloaderForFile(QUrl UrlFile, QFileInfo file, QObject *parent) : QObject(parent)
{
    initUrlFile(UrlFile);
    initSaveFile(file);

    manager = new QNetworkAccessManager();
}

DownloaderForFile::~DownloaderForFile()
{

}

bool DownloaderForFile::initUrlFile(QUrl url)
{
    if (!(url.isValid()))
    {
        return false;
    }

    urlFile = new QUrl (url);
    return true;
}

bool DownloaderForFile::initSaveFile(QFileInfo file)
{
    if (!(file.isFile()))
    {
        return false;
    }

    saveFile = new QFileInfo (file);
    return true;
}

bool DownloaderForFile::startDownloading()
{
    QNetworkRequest request;
    request.setUrl(*urlFile);
    reply = manager->get(request);
    connect(reply, &QIODevice::readyRead, this, DownloaderForFile::readyReadDownload);
    connect(reply, &QNetworkReply::finished, this, DownloaderForFile::finishedDownload);

    downloadingFile = new QFile (saveFile->absoluteFilePath());
    downloadingFile->open(QIODevice::WriteOnly);
}

bool DownloaderForFile::cancelDownloading()
{
    reply->abort();
    return true;
}

void DownloaderForFile::readyReadDownload()
{
    downloadingFile->write(reply->readAll());
}

void DownloaderForFile::finishedDownload()
{
    downloadingFile->close();
    QStringList *response = new QStringList ();
    response->operator <<(saveFile->absoluteFilePath());
    fileDownloaded(response);
}
