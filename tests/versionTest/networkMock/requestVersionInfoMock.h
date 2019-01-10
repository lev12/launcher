#ifndef REQUESTVERSIONINFOMOCK_H
#define REQUESTVERSIONINFOMOCK_H

#include "network/requestVersionInfo.h"
#include <QTimer>

class RequestVersionInfoMock : public RequestVersionInfo
{
    Q_OBJECT
public:
    RequestVersionInfoMock(QString &App,QString &Ver);
    virtual bool parse(QByteArray data);
private:
    QString *app;
    QString *ver;
private slots:
    void recive ();
};

#endif // REQUESTVERSIONINFOMOCK_H
