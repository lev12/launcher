#include "network.h"

Network::Network(Log *plog)
{
    if (plog != NULL)
    {
        log = plog;
    }
    netConfig = new QNetworkConfigurationManager ();
    isConnect = new bool;
    portServer = new unsigned short;
    addressServer = new QString;
    token = new QString ("todo");
    initConnect();
}

bool Network::initConnect()
{    
    *isConnect = netConfig->isOnline();
    connect(netConfig, QNetworkConfigurationManager::onlineStateChanged, this, Network::setConnectState);

    *portServer = QString(cfgLauncher.get("PortServer").at(0)).toShort();
    *addressServer = cfgLauncher.get("DomainServer").at(0);
    if(QString::number(*portServer) != cfgLauncher.errorResponse &&
       *addressServer != cfgLauncher.errorResponse)
    {
        if (*isConnect)
        {
            *isConnect = pingServer(*addressServer,*portServer);
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
AbstractRequest* Network::getVersionList(QString appName)
{
    if (*isConnect)
    {
        AbstractRequest *getVerList = new RequestVersionsList (addressServer,*portServer,*token,appName);
        return getVerList;
    }
    return NULL;
}

AbstractRequest* Network::getActualVersion (QString appName)
{
    if (*isConnect)
    {
        AbstractRequest *getActVer = new requestActualVersion (addressServer,*portServer,*token,appName);
        return getActVer;
    }
    return NULL;
}

/*AbstractRequest* Network::getSizeVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        AbstractRequest *getSizeVersion = new AbstractRequest (appName,0);
        return getSizeVersion;
    }
    return NULL;
}*/

AbstractRequest* Network::getFileList(QString appName, QString verName)
{
    if (*isConnect)
    {
        AbstractRequest *getFileList = new RequestFileListVersion (addressServer,*portServer,*token,appName,verName);
        return getFileList;
    }
    return NULL;
}

AbstractRequest* Network::getCheckVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        AbstractRequest *getCheckVersion = new RequestCheckVersion (addressServer,*portServer,*token,appName,verName);
        return getCheckVersion;
    }
    return NULL;
}

AbstractRequest *Network::getVersion(QString appName, QString verName)
{
    if (*isConnect)
    {
        AbstractRequest *getVer = new RequestVersion (addressServer,*portServer,*token,&appName,&verName);
        return getVer;
    }
    return NULL;
}

AbstractRequest *Network::getFile(QUrl url, QFileInfo file)
{
    if (*isConnect)
    {
        RequestFile *getFl = new RequestFile (url,file);
        return getFl;
    }
    return NULL;
}

/*AbstractRequest* Network::getFileSize (QString appName, QString verName, QString file)
{
    if (*isConnect)
    {
        AbstractRequest *getFileSize = new AbstractRequest (appName,0);
        return getFileSize;
    }
    return NULL;
}*/

AbstractRequest *Network::getVerInfo(QString appName, QString verName)
{
    if (*isConnect)
    {
        AbstractRequest *getVerInfo = new RequestVersionInfo (addressServer,*portServer,*token,appName,verName);
        return getVerInfo;
    }
    return NULL;
}

AbstractRequest *Network::getAppInfo(QString appName)
{
    if (*isConnect)
    {
        AbstractRequest *getAppInfo = new requestAppicationInfo (addressServer,*portServer,*token,appName);
        return getAppInfo;
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
        *isConnect = pingServer(*addressServer,*portServer);
    }
    qDebug () << "net state:" << *isConnect;
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


