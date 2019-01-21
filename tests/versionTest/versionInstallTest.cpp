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
    versionData::loadInstallVersionData();
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
    Config cfgL(":/launcher config.cfg");
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

void VersionInstallTest::test_initNoCfg_data()
{
    loadDataVersion ();
}

void VersionInstallTest::test_initNoCfg()
{
    QFETCH (QString,pathVersion);
    int cfg = qrand()%2;
    qDebug () << cfg;
    if (!cfg)
    {
        QString cfgFilePath (pathVersion);
        cfgFilePath.append("/version_config.cfg");
        qDebug () << cfgFilePath;
        QFile cfgFile (cfgFilePath);
        cfg = !cfgFile.remove();
    }
    qDebug () << cfg;
    NetworkMock *network = new NetworkMock (false);

    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;
    try
    {
        VersionInstall *versionInstall = new VersionInstall (appName,pathVersion,network);
    }
    catch (std::exception &e)
    {
        QVERIFY (!cfg);
    }
    QVERIFY (!cfg);
}

void VersionInstallTest::test_deleteFiles_data()
{
    loadDataVersion ();
}

void VersionInstallTest::test_deleteFiles()
{
    Config cfgL(":/launcher config.cfg");
    Network *network = new Network (cfgL.get("ipServer").at(0),QString(cfgL.get("portServer").at(0)).toUShort());
    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;
    QFETCH (QString,pathVersion);
    VersionInstall *versionInstall = new VersionInstall (appName,pathVersion,network);
    versionInstall->deleteAllFile();
}

void VersionInstallTest::cleanupTestCase()
{
    QDir ("./").rmdir("versionTestData");
}
