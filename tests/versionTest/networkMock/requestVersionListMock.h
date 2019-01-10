#ifndef REQUESTVERSIONLIST_H
#define REQUESTVERSIONLIST_H

#include "network/requestVersionsList.h"
#include <QTimer>
#include <QObject>
#include <QtTest/QtTest>

class RequestVersionListMock : public RequestVersionsList
{
    Q_OBJECT
public:
    RequestVersionListMock(QString &serverAddress, unsigned short serverPort, QString &token, QString &App);
    virtual bool parse(QByteArray data);
private:
    QString *app;
private slots:
    void recive ();
};

#endif // REQUESTVERSIONLIST_H
