#ifndef REQUESTCHECKVERSIONMOCK_H
#define REQUESTCHECKVERSIONMOCK_H

#include "network/requestCheckVersion.h"
#include <QTimer>

class RequestCheckVersionMock : public RequestCheckVersion
{
public:
    RequestCheckVersionMock(QString App, QString Ver);
    virtual bool parse(QByteArray data);
private:
    QString *app;
    QString *ver;
private slots:
    void recive ();
};

#endif // REQUESTCHECKVERSIONMOCK_H
