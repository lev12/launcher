#ifndef REQUESTVERSIONINFO_H
#define REQUESTVERSIONINFO_H

#include "abstractRequestForVersion.h"

class RequestVersionInfo : public AbstractRequestForVersion
{
public:
    RequestVersionInfo(QString serverAddress, unsigned short serverPort, QString token, QString app, QString ver);
    virtual bool parse (QByteArray data);
private:
    const QString method = "versionInfo";
};

#endif // REQUESTVERSIONINFO_H
