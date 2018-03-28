#include "network.h"

Network::Network(Log *plog)
{
    log = plog;
    cfg = new Config();
    netConfig = new QNetworkConfigurationManager ();

    isConnect = new bool;
    *isConnect = netConfig->isOnline();
    connect(netConfig, QNetworkConfigurationManager::onlineStateChanged, this, Network::setConnectState);
}

bool Network::isConnected()
{
    if (isConnect == NULL) return false;
    return *isConnect;
}

Network::~Network()
{
    delete isConnect;
}

//get request
Downloader* Network::getVersionList(QString appName)
{
    if (*isConnect)
    {
        Downloader *getVerList = new Downloader (appName,0);
        getVerList->requestVersionList();
        return getVerList;
    }
    return NULL;
}

Downloader* Network::getActualVersion (QString appName)
{
    if (*isConnect)
    {
        Downloader *getActVer = new Downloader (appName,0);
        getActVer->requestActualVersion();
        return getActVer;
    }
    return NULL;
}

Downloader* Network::getExeFile(QString appName, QString verName)
{
    if (*isConnect)
    {
        Downloader *getExeFile = new Downloader (appName,0);
        getExeFile->requestExeFileVersion();
        return getExeFile;
    }
    return NULL;
}

Downloader* Network::getSizeVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        Downloader *getSizeVersion = new Downloader (appName,0);
        getSizeVersion->requestSizeVersion();
        return getSizeVersion;
    }
    return NULL;
}

Downloader* Network::getFileList(QString appName, QString verName)
{
    if (*isConnect)
    {
        Downloader *getFileList = new Downloader (appName,0);
        getFileList->requestFileListVersion();
        return getFileList;
    }
    return NULL;
}

Downloader* Network::getCheckVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        Downloader *getCheckVersion = new Downloader (appName,0);
        getCheckVersion->requestCheckVersion();
        return getCheckVersion;
    }
    return NULL;
}

DownloaderForVersion* Network::getVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        DownloaderForVersion *getVer = new DownloaderForVersion(appName, verName, 0);
        return getVer;
    }
    return NULL;
}

DownloaderForFile* Network::getFile(QUrl url, QFileInfo file)
{
    if (*isConnect)
    {
        DownloaderForFile *getFl = new DownloaderForFile (url,file, 0);
        return getFl;
    }
    return NULL;
}

Downloader* Network::getFileSize (QString appName, QString verName, QString file)
{
    if (*isConnect)
    {
        Downloader *getFileSize = new Downloader (appName,0);
        getFileSize->requestFileSize();
        return getFileSize;
    }
    return NULL;
}

Downloader *Network::getAppInfo(QString appName)
{
    if (*isConnect)
    {
        Downloader *getAppInfo = new Downloader (appName,0);
        getAppInfo->requestApplicationInfo();
        return getAppInfo;
    }
    return NULL;
}

void Network::setConnectState(bool state)
{
    *isConnect = state;
    return;
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


