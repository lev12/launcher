#ifndef VERSIONVONTROLLERTEST_H
#define VERSIONVONTROLLERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "versionController.h"
#include "versiondata.h"
#include "networkMock/networkMock.h"
Q_DECLARE_METATYPE (QList<NetworkData>*)

class VersionControllerTest : public QObject
{
    Q_OBJECT
private:
    QDir *rootFolderWithVersions;
    
    void loadDataVersionController ();
    int removeFolder(QDir &dir);
private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_getListVersion_data ();
    void test_getListVersion ();
    void test_getListInsallVersion();
    void test_getListNoInstallVersion();
    void test_getVersion_data();
    void test_getVersion();

    void test_deleteAllVersion();
    void test_updateVersionsList();
    void test_downloadVersion();

    void test_isFoundVersions();
};

#endif // VERSIONVONTROLLERTEST_H
