#ifndef REQUESTVERSIONSLIST_H
#define REQUESTVERSIONSLIST_H

#include "abstractRequestForApplication.h"

class RequestVersionsList : public AbstractRequestForApplication
{
public:
    RequestVersionsList(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "versionList";
};

#endif // REQUESTVERSIONSLIST_H
