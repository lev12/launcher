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

QString versionData::randomString()
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 12; // assuming you want random strings of 12 characters

    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}


