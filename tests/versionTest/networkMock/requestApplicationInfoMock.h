#ifndef REQUESTAPPICATIONINFOMOCK_H
#define REQUESTAPPICATIONINFOMOCK_H

#include "network/requestApplicationInfo.h"
#include <QTimer>

class RequestApplicationInfoMock : public RequestApplicationInfo
{
public:
    RequestApplicationInfoMock(QString &App);
    virtual bool parse(QByteArray data);
private:
    QString *app;
private slots:
    void recive ();
};

#endif // REQUESTAPPICATIONINFOMOCK_H
