#include "abstractVersionTest.h"

AbstractVersionTest::AbstractVersionTest()
{

}

void AbstractVersionTest::test_getFullName_data()
{
    versionData::loadVersionNameData();
}

void AbstractVersionTest::test_getFullName()
{
    QFETCH(QString, versionName);
    QFETCH(VersionType, versionTypeResult);
    QFETCH(int, versionNumberResult);
    QFETCH(QString, versionNameSpaceResult);
    QFETCH(QString, versionNameUnderscoreResult);

    initVerName(versionName);
    QCOMPARE(getVersionType(),versionTypeResult);
    QCOMPARE(getVersionNumber(),versionNumberResult);
    QCOMPARE(getFullName(), versionNameSpaceResult);
}

void AbstractVersionTest::test_getIsInstall()
{
    initIsInatall(true);
    QCOMPARE (getIsInstall(),true);
    initIsInatall(false);
    QCOMPARE (getIsInstall(),false);
}

void AbstractVersionTest::test_getAppName()
{
    QString randomstr = versionData::randomString();
    qDebug () << "app name:     " << randomstr;
    initAppName(randomstr);
    QCOMPARE (getAppName(),randomstr);
}

void AbstractVersionTest::test_versionTypeToString_data()
{
    QTest::addColumn<VersionType>("versionType");
    QTest::addColumn<QString>("versionTypeStringResult");

    QTest::newRow("pre-alpha") << pre_alpha << "pre-alpha";
    QTest::newRow("alpha") << alpha << "alpha";
    QTest::newRow("beta") << beta << "beta";
    QTest::newRow("release") << release << "release";
    QTest::newRow("null") << null << "null";
}

void AbstractVersionTest::test_versionTypeToString()
{
    QFETCH (VersionType,versionType);
    QFETCH (QString,versionTypeStringResult);

    QCOMPARE(AbstractVersion::versionTypeToString(versionType),versionTypeStringResult);
}

void AbstractVersionTest::test_stringToVersionType_data()
{
    QTest::addColumn<QString>("versionTypeString");
    QTest::addColumn<VersionType>("versionTypeResult");

    QTest::newRow("pre-alpha") << "pre-alpha" << pre_alpha;
    QTest::newRow("alpha") << "alpha" << alpha;
    QTest::newRow("beta") << "beta" << beta;
    QTest::newRow("release") << "release" << release;
    QString randomStr = versionData::randomString();
    qDebug () << "random string test:    " << randomStr;
    QTest::newRow("null") << randomStr << null;
}

void AbstractVersionTest::test_stringToVersionType()
{
    QFETCH (QString, versionTypeString);
    QFETCH (VersionType, versionTypeResult);

    QCOMPARE(AbstractVersion::stringToVersionType(versionTypeString), versionTypeResult);
}

void AbstractVersionTest::test_strToPlatform_data()
{
    QTest::addColumn<QString>("paltformString");
    QTest::addColumn<PlatformType>("paltformStringResult");

    QTest::newRow("PC") << "PC" << PC;
    QTest::newRow("MAC") << "MAC" << MAC;
    QTest::newRow("Android") << "Android" << Android;
    QTest::newRow("IOS") << "IOS" << IOS;
    QTest::newRow("XBox") << "XBox" << XBox;
    QTest::newRow("PlayStation") << "PlayStation" << PlayStation;
    QString randomStr = versionData::randomString();
    qDebug () << "random string test:    " << randomStr;
    QTest::newRow("null") << randomStr << Null;
}

void AbstractVersionTest::test_strToPlatform()
{
    QFETCH (QString,paltformString);
    QFETCH (PlatformType,paltformStringResult);

    QCOMPARE (AbstractVersion::stringToPlatform(paltformString),paltformStringResult);
}
