#ifndef REQUESTACTUALVERSIONMOCK_H
#define REQUESTACTUALVERSIONMOCK_H

#include "network/requestActualVersion.h"
#include "versionController.h"
#include <QTimer>

class RequestActualVersionMock : public RequestActualVersion
{
    Q_OBJECT
public:
    RequestActualVersionMock(QString &App);
    virtual bool parse(QByteArray data);
private:
    QString *app;
private slots:
    void recive ();
};

#endif // REQUESTACTUALVERSIONMOCK_H
