#ifndef REQUESTAPPLICATIONLISTMOCK_H
#define REQUESTAPPLICATIONLISTMOCK_H

#include "network/requestApplicationList.h"
#include <QTimer>

class RequestApplicationListMock : public RequestApplicationList
{
    Q_OBJECT
public:
    RequestApplicationListMock();
    virtual bool parse(QByteArray data);
private slots:
    void recive ();
};

#endif // REQUESTAPPLICATIONLISTMOCK_H
