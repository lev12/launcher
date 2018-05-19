#ifndef REQUESTAPPLICATIONLIST_H
#define REQUESTAPPLICATIONLIST_H

#include "abstractRequest.h"

class RequestApplicationList : public AbstractRequest
{
public:
    RequestApplicationList(QString serverAddress, int serverPort, QString token);
    virtual bool parse (QByteArray data);
private:
    const QString method = "appicationList";
};

#endif // REQUESTAPPLICATIONLIST_H
