#include "network.h"

Network::Network(Log *plog)
{
    log = plog;
    cfg = new Config();
}

Network::~Network()
{

}

//get request
Downloader* Network::getVersionList(QString appName)
{
    Downloader *getVerList = new Downloader (appName,0);
    getVerList->requestVersionList();
    return getVerList;
}

Downloader* Network::getActualVersion (QString appName)
{
    Downloader *getActVer = new Downloader (appName,0);
    getActVer->requestActualVersion();
    return getActVer;
}

Downloader* Network::getExeFile(QString appName, QString verName)
{
    Downloader *getExeFile = new Downloader (appName,0);
    getExeFile->requestExeFileVersion();
    return getExeFile;
}

Downloader* Network::getSizeVersion(QString appName, QString verName)
{
    Downloader *getSizeVersion = new Downloader (appName,0);
    getSizeVersion->requestSizeVersion();
    return getSizeVersion;
}

Downloader* Network::getFileList(QString appName, QString verName)
{
    Downloader *getFileList = new Downloader (appName,0);
    getFileList->requestFileListVersion();
    return getFileList;
}

Downloader* Network::getCheckVersion(QString appName, QString verName)
{
    Downloader *getCheckVersion = new Downloader (appName,0);
    getCheckVersion->requestCheckVersion();
    return getCheckVersion;
}

DownloaderForVersion* Network::getVersion(QString appName, QString verName)
{
    DownloaderForVersion *getVer = new DownloaderForVersion(appName, verName, 0);
    return getVer;
}

DownloaderForFile* Network::getFile(QUrl url, QFileInfo file)
{
    DownloaderForFile *getFl = new DownloaderForFile (url,file, 0);
    return getFl;
}

Downloader* Network::getFileSize (QString appName, QString verName, QString file)
{
    Downloader *getFileSize = new Downloader (appName,0);
    getFileSize->requestFileSize();
    return getFileSize;
}

/*bool Network::parseUploadLog(QByteArray data)
{
    if (data == "file:error:")
    {
        return true;
    }

    QFile file (uploadFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug () << "not open file upload";
    }

    if (data == "log:accepted:" || data == "log:reception:")
    {
        static int countBlock = qFloor(file.size()/8192)+1;
        static int numberBlock;

        if (countBlock != numberBlock)
        {
            QByteArray buffer;
            buffer = file.read(8192);
            /*server->write(buffer);
            server->waitForBytesWritten();
            server->flush();
            numberBlock++;
            return true;
        }
        else
        {
            //server->write("log:upload:end:");
            file.close();
            return true;
        }
     }

    return false;
}*/


