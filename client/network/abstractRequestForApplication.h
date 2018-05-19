#ifndef ABSTRACTREQUESTFORAPPLICATION_H
#define ABSTRACTREQUESTFORAPPLICATION_H

#include "abstractRequest.h"

class AbstractRequestForApplication : public AbstractRequest
{
public:
    AbstractRequestForApplication(QString serverAddress, unsigned short serverPort);
    virtual QString getRequestParam(QString token, QString app);
};

#endif // ABSTRACTREQUESTFORAPPLICATION_H
