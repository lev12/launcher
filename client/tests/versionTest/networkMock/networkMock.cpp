#include "networkMock.h"

NetworkMock::NetworkMock(bool isConnected) : Network (QString("localhost"),80)
{
    isConnectMock = new bool;
    setIsConnectMock(isConnected);
}

AbstractRequest *NetworkMock::getActualVersion(QString appName)
{
    if (*isConnectMock)
    {
        RequestActualVersionMock *ractver = new RequestActualVersionMock (appName);
        return ractver;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getApplicationList()
{
    if (*isConnectMock)
    {
        AbstractRequest *tapplist = new RequestApplicationListMock ();
        return tapplist;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getFileListVersion(QString appName, QString verName)
{
    if (*isConnectMock)
    {
        AbstractRequest *rfilelistver = new RequestFileListVersionMock (appName,verName);
        return rfilelistver;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getCheckVersion(QString appName, QString verName)
{
    if (*isConnectMock)
    {
        AbstractRequest *rchver = new RequestCheckVersionMock (appName,verName);
        return rchver;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getFile(QUrl url, QFileInfo file)
{
    if (*isConnectMock)
    {
        AbstractRequest *rfile = new RequestFileMock (url,file);
        return rfile;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getVersionInfo(QString appName, QString verName)
{
    if (*isConnectMock)
    {
        AbstractRequest *rverinfo = new RequestVersionInfoMock (appName,verName);
        return rverinfo;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getAppInfo(QString appName)
{
    if (*isConnectMock)
    {
        AbstractRequest *rappinfo = new RequestApplicationInfoMock (appName);
        return rappinfo;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getVersion(QString &appName, QString &verName, QDir &saveFolderPath)
{
    if (*isConnectMock)
    {
        AbstractRequest *rver = new RequestVersionMock (*addressServer,*portServer,*token,appName,verName,saveFolderPath);
        return rver;
    }
    return NULL;
}

AbstractRequest *NetworkMock::getVersionList(QString appName)
{
    if (*isConnectMock)
    {
        AbstractRequest *rverlist = new RequestVersionListMock (*addressServer,*portServer,*token,appName);
        return rverlist;
    }
    return NULL;
}

bool NetworkMock::isConnected()
{
    return *isConnectMock;
}

void NetworkMock::setIsConnectMock(bool value)
{
    *isConnectMock = value;
}
