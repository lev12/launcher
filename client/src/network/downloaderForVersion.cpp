#include "downloaderForVersion.h"

DownloaderForVersion::DownloaderForVersion(QString AppName, QString VerName, QObject *parent) : QObject(parent)
{
    appName = new QString (AppName);
    verName = new QString (VerName);

    QString pathVer = ".\\";
    pathVer.append(_Data);
    pathVer.append("/");
    pathVer.append(AppName);
    pathVer.append("/");
    pathVer.append(VerName);
    verDir = new QDir (pathVer);

    getCheckVersion();
}

DownloaderForVersion::~DownloaderForVersion()
{

}

bool DownloaderForVersion::getCheckVersion()
{
    Downloader getCheckVer(*appName, NULL);
    if (!getCheckVer.requestCheckVersion())
    {
        return false;
    }

    QObject::connect(&getCheckVer, &Downloader::replyServer, this, &DownloaderForVersion::replyCheckVersion);
    return true;
}

bool DownloaderForVersion::getSizeVersion()
{
    Downloader getSizeVer(*appName, NULL);
    if (!getSizeVer.requestCheckVersion())
    {
        return false;
    }

    QObject::connect(&getSizeVer, &Downloader::replyServer, this, &DownloaderForVersion::replySizeVersion);
    return true;
}

bool DownloaderForVersion::getExeFile()
{
    Downloader getExe(*appName, NULL);
    if (!getExe.requestCheckVersion())
    {
        return false;
    }

    QObject::connect(&getExe, &Downloader::replyServer, this, &DownloaderForVersion::replyExeFile);
    return true;
}

bool DownloaderForVersion::getFileList()
{
    Downloader getFileList(*appName, NULL);
    if (!getFileList.requestCheckVersion())
    {
        return false;
    }

    QObject::connect(&getFileList, &Downloader::replyServer, this, &DownloaderForVersion::replyFileList);
    return true;
}

bool DownloaderForVersion::getFile(QUrl urlfile, QFileInfo file)
{
    DownloaderForFile *getFileOnServer = new DownloaderForFile (urlfile, file, 0);
    if (!getFileOnServer->startDownloading())
    {
        return false;
    }

    connect(getFileOnServer, &DownloaderForFile::fileDownloaded,
                     this, &DownloaderForVersion::replyFile);
    return true;
}

void DownloaderForVersion::replyCheckVersion(QStringList *response)
{
    if (response->at(0) == "true")
    {
        isVersion = true;
        getSizeVersion();
        return;
    }
    else if (response->at(0) == "false")
    {
        isVersion = false;
        return;
    }
    else
    {
        //log warring
        isVersion = false;
        return;
    }
}

void DownloaderForVersion::replySizeVersion(QStringList *response)
{
    verSize = QString(response->at(0)).toInt();
    checkFreeStorage();
    getExeFile();
    return;
}

void DownloaderForVersion::replyExeFile(QStringList *response)
{
    exePath = new QString (response->at(0));
    getFileList();
    return;
}

void DownloaderForVersion::replyFileList(QStringList *response)
{
    fileListVersion = new QStringList (*response);
    downloadNextFile();
    return;
}

void DownloaderForVersion::replyFile(QStringList *response)
{
    currentDonloadFile++;
    downloadNextFile();
}

bool DownloaderForVersion::checkFreeStorage()
{
    if (QStorageInfo(*verDir).bytesFree() >= verSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DownloaderForVersion::downloadNextFile()
{
    if (currentDonloadFile <= fileListVersion->length())
    {
        QString urlStr (AdderssServer);
        urlStr.append("app/");
        urlStr.append(appName);
        urlStr.append("/");
        urlStr.append(verName);
        urlStr.append(fileListVersion->at(currentDonloadFile));
        QUrl *url = new QUrl (urlStr);

        QString filePathStr (verDir->absolutePath());
        filePathStr.append("/");
        filePathStr.append(fileListVersion->at(currentDonloadFile));
        QFileInfo *filePath = new QFileInfo(filePathStr);
        getFile(*url, *filePath);
    }
    else
    {
        checkDownload();
    }
    return true;
}

bool DownloaderForVersion::checkDownload()
{
    QStringList *response = new QStringList ();
    complitDownload (response);
    return true;
}
