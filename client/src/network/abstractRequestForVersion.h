#ifndef ABSTRACTREQUESTFORVERSION_H
#define ABSTRACTREQUESTFORVERSION_H

#include "abstractRequest.h"

class AbstractRequestForVersion : public AbstractRequest
{
public:
    AbstractRequestForVersion(QString *serverAddress, unsigned short serverPort);
    virtual QString getRequestParam (QString token,QString app,QString ver);
private:

};

#endif // ABSTRACTREQUESTFORVERSION_H
