#include "requestVersionMock.h"

RequestVersionMock::RequestVersionMock(QString &addressServer,unsigned short &portServer,QString &Token, QString &appName, QString &verName, QDir &saveFolderPath) :
    RequestVersion (addressServer,portServer,Token,appName,verName,saveFolderPath)
{
    
}

bool RequestVersionMock::parse(QByteArray data)
{
    
}
