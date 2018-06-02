#include "network.h"

Network::Network(Log *plog)
{
    if (plog != NULL)
    {
        log = plog;
    }
    netConfig = new QNetworkConfigurationManager ();
    isConnect = new bool;
    PortServer = new unsigned short;
    AdderssServer = new QString;
    initConnect();

    /*rcv = new RequestCheckVersion(*AdderssServer,*PortServer,"dffe","Electrical_Simulator","alpha_45");
    connect(rcv, AbstractRequest::replyServer, this, Network::reschver);
    ral = new RequestApplicationList(*AdderssServer,*PortServer,"vhshvuhivhsiuhish");
    */
}

bool Network::initConnect()
{    
    *isConnect = netConfig->isOnline();
    connect(netConfig, QNetworkConfigurationManager::onlineStateChanged, this, Network::setConnectState);

    *PortServer = QString(cfgLauncher.get("PortServer").at(0)).toShort();
    *AdderssServer = cfgLauncher.get("DomainServer").at(0);
    if(QString::number(*PortServer) != cfgLauncher.errorResponse &&
       *AdderssServer != cfgLauncher.errorResponse)
    {
        if (*isConnect)
        {
            *isConnect = pingServer(*AdderssServer,*PortServer);
        }
    }


    return true;
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

Downloader *Network::getVerInfo(QString appName, QString verName)
{
    if (*isConnect)
    {
        Downloader *getVerInfo = new Downloader (appName,0);
        getVerInfo->requestVersionInfo();
        return getVerInfo;
    }
    return NULL;
}

bool Network::pingServer(QString adderss, qint16 port)
{
    QTcpSocket socket;
    socket.connectToHost(adderss,port);
    if (socket.waitForConnected())
    {
        return true;
    }
    return false;
}

void Network::setConnectState(bool state)
{
    *isConnect = state;
    if (state)
    {
        *isConnect = pingServer(*AdderssServer,*PortServer);
    }
    qDebug () << "net state:" << *isConnect;
    return;
}

void Network::reschver(QList<NetworkData> *response)
{
    qDebug () << response->at(0).value;
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


