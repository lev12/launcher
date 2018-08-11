#ifndef TST_INSTALLVERSION_H
#define TST_INSTALLVERSION_H

#include <QtTest/QtTest>
#include <QObject>
#include <QDir>
#include <QString>
#include "versionInstall.h"
#include "versiondata.h"

class VersionInstallTest : public QObject
{
    Q_OBJECT
public:
    explicit VersionInstallTest();
    ~VersionInstallTest();
    static loadDataVersion ();
    QDir *versionData;
private slots:
    void initTestCase();
    void test_init_data ();
    void test_init ();
    void test_deleteFiles_data ();
    void test_deleteFiles ();
    void test_initNoCfg_data ();
    void test_initNoCfg ();
    void cleanupTestCase();
};

#endif // TST_INSTALLVERSION_H
