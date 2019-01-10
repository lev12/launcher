#ifndef RESQUSTACTUALVERSION_H
#define RESQUSTACTUALVERSION_H

#include "abstractRequestForApplication.h"

class RequestActualVersion : public AbstractRequestForApplication
{

public:
    RequestActualVersion();
    RequestActualVersion(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    void send();
    virtual bool parse (QByteArray data);
private:
    const QString method = "actualVersion";
};

#endif // RESQUSTACTUALVERSION_H
