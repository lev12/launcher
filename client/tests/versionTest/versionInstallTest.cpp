#include "versionInstallTest.h"

VersionInstallTest::VersionInstallTest()
{
    versionData = new QDir (":/versionTestData");
}

VersionInstallTest::~VersionInstallTest()
{

    delete versionData;
}

VersionInstallTest::loadDataVersion()
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

void VersionInstallTest::initTestCase()
{
    QString rootdirname ("versionTestData");
    QString rootdir ("./");
    rootdir.append(rootdirname);
    if (!QDir(rootdir).exists())
    {
        QStringList lstDirs = versionData->entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);

        foreach (QString tempDir, lstDirs)
        {
            QString tempPath;
            tempPath.append(rootdirname);
            tempPath.append(QString("/"));
            tempPath.append(tempDir);
            QDir tempMkDir ("./");
            tempMkDir.mkpath(tempPath);
            QString tempPathRes (":/");
            tempPathRes.append(rootdirname);
            tempPathRes.append("/");
            tempPathRes.append(tempDir);
            foreach (QString tempFile, QDir(tempPathRes).entryList(QDir::Files))
            {
                QString tempFilePath (tempPathRes);
                tempFilePath.append("/");
                tempFilePath.append(tempFile);
                QString tempNewFilePath (tempPath);
                tempNewFilePath.append("/");
                tempNewFilePath.append(tempFile);
                QFile::copy(tempFilePath,tempNewFilePath);
            }
        }
    }
}

void VersionInstallTest::test_init_data()
{
    loadDataVersion ();
}

void VersionInstallTest::test_init()
{
    Config cfgL(":/versionTestData/launcher config.cfg");
    Network *network = new Network (cfgL.get("DomainServer").at(0),QString(cfgL.get("PortServer").at(0)).toUShort());
    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;

    QFETCH (QString,pathVersion);
    QFETCH (VersionType,versionTypeResult);
    QFETCH (int,versionNumberResult);
    QFETCH (QString,versionNameSpaceResult);
    QFETCH (QString,versionNameUnderscoreResult);
    QFETCH (QString,startFileName);
    QFETCH (int,versionSizeResult);
    QFETCH (int,versionCountFile);
    QFETCH (bool,versionValidate);

    bool isVersion = VersionInstall::checkVersion(QFileInfo(pathVersion));
    QCOMPARE (isVersion,versionValidate);
    if (isVersion)
    {
        QDir tempPathVersion (pathVersion);
        if (!tempPathVersion.exists())
        {
            qDebug () << tempPathVersion.absolutePath() << tempPathVersion.exists();
            QFAIL ("no exists dir");
        }
        VersionInstall *versionInstall = new VersionInstall (appName,pathVersion,network);
        QCOMPARE (versionInstall->getVersionType(),versionTypeResult);
        QCOMPARE (versionInstall->getVersionNumber(),versionNumberResult);
        QCOMPARE (versionInstall->getFullName(),versionNameSpaceResult);

        QCOMPARE (versionInstall->getStartedFileName(),startFileName);
        QFileInfo startFile (versionInstall->getStartedFilePath());
        QCOMPARE (startFile.exists(),true);
        QCOMPARE (startFile.fileName(),startFileName);

        QCOMPARE (versionInstall->getIsInstall(), true);
        QCOMPARE (versionInstall->getAppName(), appName);
        quint64 verSize = versionInstall->getVersionSize();
        QCOMPARE (verSize,(quint64) versionSizeResult);
        QCOMPARE (versionInstall->getFileList().length(),versionCountFile);
        delete versionInstall;
    }

}

void VersionInstallTest::test_deleteFiles_data()
{
    loadDataVersion ();
}

void VersionInstallTest::test_deleteFiles()
{
    Config cfgL(":/data/versionTestData/launcher config.cfg");
    Network *network = new Network (cfgLauncher.get("DomainServer").at(0),QString(cfgLauncher.get("PortServer").at(0)).toUShort());
    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;
    QFETCH (QString,pathVersion);
    VersionInstall *versionInstall = new VersionInstall (appName,pathVersion,network);
    versionInstall->deleteAllFile();
}

void VersionInstallTest::test_initNoCfg_data()
{

}

void VersionInstallTest::test_initNoCfg()
{

}

void VersionInstallTest::cleanupTestCase()
{
    QDir ("./").rmdir("versionTestData");
}
