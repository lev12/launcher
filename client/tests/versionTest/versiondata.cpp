#include "versiondata.h"

versionData::versionData(QObject *parent) : QObject(parent)
{

}

void versionData::loadVersionNameData()
{
    QTest::addColumn<QString>("versionName");
    QTest::addColumn<VersionType>("versionTypeResult");
    QTest::addColumn<int>("versionNumberResult");
    QTest::addColumn<QString>("versionNameSpaceResult");
    QTest::addColumn<QString>("versionNameUnderscoreResult");

    QTest::newRow("pre-alpha space") << "pre-alpha 27" << pre_alpha << 27 << "pre-alpha 27" << "pre-alpha_27";
    QTest::newRow("pre_alpha space") << "pre_alpha 27" << pre_alpha << 27 << "pre-alpha 27" << "pre-alpha_27";
    QTest::newRow("alpha space") << "alpha 45" << alpha << 45 << "alpha 45" << "alpha_45";
    QTest::newRow("beta space") << "beta 45" << beta << 45 << "beta 45" << "beta_45";
    QTest::newRow("release space") << "release 45" << release << 45 << "release 45" << "release_45";
    QTest::newRow("pre-alpha underscore") << "pre-alpha_45" << pre_alpha << 45 << "pre-alpha 45" << "pre-alpha_45";
    QTest::newRow("pre_alpha underscore") << "pre_alpha_45" << pre_alpha << 45 << "pre-alpha 45" << "pre-alpha_45";
    QTest::newRow("alpha underscore") << "alpha_45" << alpha << 45 << "alpha 45" << "alpha_45";
    QTest::newRow("beta underscore") << "beta_45" << beta << 45 << "beta 45" << "beta_45";
    QTest::newRow("release underscore") << "release_45" << release << 45 << "release 45" << "release_45";
}

void versionData::loadInstallVersionData()
{
    QTest::addColumn<QString>("pathVersion");
    QTest::addColumn<VersionType>("versionTypeResult");
    QTest::addColumn<int>("versionNumberResult");
    QTest::addColumn<QString>("versionNameSpaceResult");
    QTest::addColumn<QString>("versionNameUnderscoreResult");
    QTest::addColumn<QString>("startFileName");
    QTest::addColumn<int>("versionSizeResult");
    QTest::addColumn<int>("versionCountFile");
    QTest::addColumn<bool>("versionValidate");
    
    QTest::newRow("pre-alpha space") << "./versionTestData/pre-alpha 66" << pre_alpha << 66 << "pre-alpha 66" << "pre-alpha_66" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("pre_alpha space") << "./versionTestData/pre_alpha 27" << pre_alpha << 27 << "pre-alpha 27" << "pre-alpha_27" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("alpha space") << "./versionTestData/alpha 88" << alpha << 88 << "alpha 88" << "alpha_88" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("beta space") << "./versionTestData/beta 64" << beta << 64 << "beta 64" << "beta_64" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("release space") << "./versionTestData/release 34" << release << 34 << "release 34" << "release_34" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("pre-alpha underscore") << "./versionTestData/pre-alpha_6" << pre_alpha << 6 << "pre-alpha 6" << "pre-alpha_6" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("pre_alpha underscore") << "./versionTestData/pre_alpha_4" << pre_alpha << 4 << "pre-alpha 4" << "pre-alpha_4" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("alpha underscore") << "./versionTestData/alpha_96" << alpha << 96 << "alpha 96" << "alpha_96" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("beta underscore") << "./versionTestData/beta_566" << beta << 566 << "beta 566" << "beta_566" << "simulatorelectricity.exe" << 359461 << 2 << true;
    QTest::newRow("release underscore") << "./versionTestData/release_58" << release << 58 << "release 58" << "release_58" << "simulatorelectricity.exe" << 359461 << 2 << true;
    
}

QString versionData::randomString()
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 12;

    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}


