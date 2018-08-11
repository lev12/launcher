#ifndef TST_ABSTRACTVERSION_H
#define TST_ABSTRACTVERSION_H

#include <QObject>
#include <QtTest/QtTest>
#include "abstractVersion.h"
#include "versiondata.h"

class AbstractVersionTest : public AbstractVersion
{
    Q_OBJECT
public:
    explicit AbstractVersionTest();
private slots:
    void test_getFullName_data();
    void test_getFullName ();
    void test_getIsInstall ();
    void test_getAppName ();

    void test_versionTypeToString_data ();
    void test_versionTypeToString ();
    void test_stringToVersionType_data ();
    void test_stringToVersionType ();
    void test_strToPlatform_data ();
    void test_strToPlatform ();
};

#endif // TST_ABSTRACTVERSION_H
