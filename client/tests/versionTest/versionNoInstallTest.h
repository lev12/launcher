#ifndef TST_NOINSTALLVERSION_H
#define TST_NOINSTALLVERSION_H

#include <QtTest/QtTest>
#include "versionNoInstall.h"
#include "versiondata.h"
#include <QObject>

class VersionNoInstallTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_initCase_data ();
    void test_initCase();

};

#endif // TST_NOINSTALLVERSION_H
