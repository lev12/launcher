#ifndef REQUESTCHECKVERSION_H
#define REQUESTCHECKVERSION_H

#include "abstractRequestForVersion.h"

class RequestCheckVersion : public AbstractRequestForVersion
{
public:
    RequestCheckVersion(QString *serverAddress, unsigned short serverPort, QString token, QString app, QString ver);
    virtual bool parse (QByteArray data);
private:
    const QString method = "checkVersion";
};

#endif // REQUESTCHECKVERSION_H
