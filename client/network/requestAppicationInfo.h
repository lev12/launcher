#ifndef REQUESTAPPICATIONINFO_H
#define REQUESTAPPICATIONINFO_H

#include "abstractRequestForApplication.h"

class requestAppicationInfo : public AbstractRequestForApplication
{
public:
    requestAppicationInfo(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "appicationInfo";
};

#endif // REQUESTAPPICATIONINFO_H
