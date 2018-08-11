#include "versionNoInstallTest.h"

void VersionNoInstallTest::initTestCase()
{

}

void VersionNoInstallTest::cleanupTestCase()
{

}

void VersionNoInstallTest::test_initCase_data()
{
    versionData::loadVersionNameData();
}

void VersionNoInstallTest::test_initCase()
{
    QFETCH(QString, versionName);
    QFETCH(VersionType, versionTypeResult);
    QFETCH(int, versionNumberResult);
    QFETCH(QString, versionNameSpaceResult);
    QFETCH(QString, versionNameUnderscoreResult);
    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;
    VersionNoInstall *verNoIntsall = new VersionNoInstall (appName,versionName);

    QCOMPARE(verNoIntsall->getVersionType(),versionTypeResult);
    QCOMPARE(verNoIntsall->getVersionNumber(),versionNumberResult);
    QCOMPARE(verNoIntsall->getFullName(), versionNameSpaceResult);
    QCOMPARE(verNoIntsall->getAppName(), appName);
    QCOMPARE(verNoIntsall->getIsInstall(), false);
}
