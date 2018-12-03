#ifndef REQUESTVERSIONMOCK_H
#define REQUESTVERSIONMOCK_H

#include "network/requestVersion.h"

class RequestVersionMock : virtual public RequestVersion
{
public:
    RequestVersionMock(QString &addressServer, unsigned short &portServer, QString &Token, QString &appName, QString &verName, QDir &saveFolderPath);
    virtual bool parse(QByteArray data);
};

#endif // REQUESTVERSIONMOCK_H
