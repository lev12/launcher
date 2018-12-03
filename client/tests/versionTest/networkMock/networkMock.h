#ifndef NETWORKMOCK_H
#define NETWORKMOCK_H

#include "network/network.h"
#include "requestActualVersionMock.h"
#include "requestApplicationInfoMock.h"
#include "requestApplicationListMock.h"
#include "requestCheckApplicationMock.h"
#include "requestCheckVersionMock.h"
#include "requestFileListVersionMock.h"
#include "requestFileMock.h"
#include "requestVersionInfoMock.h"
#include "requestVersionListMock.h"
#include "requestVersionMock.h"

class NetworkMock : virtual public Network
{
public:
    NetworkMock(bool isConnected);
    
    virtual AbstractRequest *getActualVersion(QString appName);
    virtual AbstractRequest *getVersionList(QString appName);
    virtual AbstractRequest *getApplicationList();
    //AbstractRequest* getSizeVersion       (QString appName, QString verName);
    virtual AbstractRequest *getFileListVersion(QString appName, QString verName);
    virtual AbstractRequest *getCheckVersion(QString appName, QString verName);
    virtual AbstractRequest* getVersion (QString &appName, QString &verName, QDir &saveFolderPath);
    virtual AbstractRequest *getFile(QUrl url, QFileInfo file);
    //AbstractRequest* getFileSize          (QString appName, QString verName, QString file);
    virtual AbstractRequest *getVersionInfo(QString appName, QString verName);
    virtual AbstractRequest *getAppInfo(QString appName);
    virtual bool isConnected();
    void setIsConnectMock(bool value);
    
private:
    bool *isConnectMock;
};

#endif // NETWORKMOCK_H
