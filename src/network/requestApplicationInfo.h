#ifndef REQUESTAPPLICATIONINFO_H
#define REQUESTAPPLICATIONINFO_H

#include "abstractRequestForApplication.h"

class RequestApplicationInfo : public AbstractRequestForApplication
{
public:
    RequestApplicationInfo();
    RequestApplicationInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "applicationInfo";
};

#endif // REQUESTAPPLICATIONINFO_H
