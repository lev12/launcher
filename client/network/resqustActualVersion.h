#ifndef RESQUSTACTUALVERSION_H
#define RESQUSTACTUALVERSION_H

#include "abstractRequestForApplication.h"

class resqustActualVersion : public AbstractRequestForApplication
{
public:
    resqustActualVersion(QString serverAddress, unsigned short serverPort,QString token,QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "actualVersion";
};

#endif // RESQUSTACTUALVERSION_H
