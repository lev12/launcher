#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QSignalSpy>
#include "network/network.h"
#include "versiondata.h"

class NetworkTest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkTest();

private:
    Config *cfg;
    QString *addressServer;
    quint16 *portServer;
private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_getActualVersion ();
    void test_getVersionList ();
    void test_getFileList ();
    void test_getCheckVersion ();
    void test_getVersion ();
    void test_getFile ();
    void test_getVerInfo ();
    void test_getAppInfo ();
public slots:
    void recive_getActualVersion (QList<NetworkData> *response);
};

#endif // NETWORKTEST_H
