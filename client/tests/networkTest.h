#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QSignalSpy>
#include <QTestEventLoop>
#include "network/network.h"
#include "versiondata.h"
#include "abstractVersion.h"
Q_DECLARE_METATYPE (QList<NetworkData>*)

class NetworkTest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkTest();

private:
    Config *cfg;
    QString *addressServer;
    quint16 *portServer;
    Network *network;
    QDir *dataFolder;

    struct metaApplication
    {
        QString app;
        QStringList ver;
        QStringList files;
    };

    QList <metaApplication*> *appList;

    void loadApplicationData (QList <metaApplication*> *metaAppData);
    void loadVersionData (QList <metaApplication*> *metaAppData);
    void loadFileData (QList <metaApplication*> *metaAppData);
private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_getApplicationList ();
    void test_getVersionList_data ();
    void test_getVersionList ();
    void test_getFileList_data ();
    void test_getFileList ();
    void test_getActualVersion_data ();
    void test_getActualVersion ();
    void test_getCheckVersion_data ();
    void test_getCheckVersion ();
    void test_getFile_data ();
    void test_getFile ();
    void test_getVersion_data ();
    void test_getVersion ();
    void test_getVersionInfo_data ();
    void test_getVersionInfo ();
    void test_getAppInfo_data ();
    void test_getAppInfo ();
};

#endif // NETWORKTEST_H
