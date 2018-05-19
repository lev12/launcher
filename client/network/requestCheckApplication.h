#ifndef REQUESTCHECKAPPLICATION_H
#define REQUESTCHECKAPPLICATION_H

#include "abstractRequestForApplication.h"

class RequestCheckApplication : public AbstractRequestForApplication
{
public:
    RequestCheckApplication(QString serverAddress, unsigned short serverPort, QString token, QString app);
    virtual bool parse (QByteArray data);
private:
    const QString method = "checkVersion";
};

#endif // REQUESTCHECKAPPLICATION_H
