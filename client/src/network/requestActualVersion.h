#ifndef RESQUSTACTUALVERSION_H
#define RESQUSTACTUALVERSION_H

#include "abstractRequestForApplication.h"

class requestActualVersion : public AbstractRequestForApplication
{
public:
    requestActualVersion(QString *serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "actualVersion";
};

#endif // RESQUSTACTUALVERSION_H
