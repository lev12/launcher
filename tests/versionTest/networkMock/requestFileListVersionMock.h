#ifndef REQUESTFILELISTVERSIONMOCK_H
#define REQUESTFILELISTVERSIONMOCK_H

#include "network/requestFileListVersion.h"
#include <QTimer>

class RequestFileListVersionMock : public RequestFileListVersion
{
public:
    RequestFileListVersionMock(QString App, QString Ver);
    virtual bool parse(QByteArray data);
private:
    QString *app;
    QString *ver;
private slots:
    void recive ();
};

#endif // REQUESTFILELISTVERSIONMOCK_H
