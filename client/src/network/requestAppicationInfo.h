#ifndef REQUESTAPPLICATIONINFO_H
#define REQUESTAPPLICATIONINFO_H

#include "abstractRequestForApplication.h"

class requestapplicationInfo : public AbstractRequestForApplication
{
public:
    requestapplicationInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "applicationInfo";
};

#endif // REQUESTAPPLICATIONINFO_H
