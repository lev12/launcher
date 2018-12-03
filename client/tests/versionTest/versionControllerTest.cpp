#include "versionControllerTest.h"

void VersionControllerTest::initTestCase()
{
    QString rootdirname ("versionControllerTestData");
    QString rootdir ("./");
    rootdir.append(rootdirname);
    rootFolderWithVersions = new QDir (rootdir);
    if (rootFolderWithVersions->exists())
    {
        removeFolder(*rootFolderWithVersions);
    }
    QDir ("./").mkdir(rootdirname);
    QDir resFolderWithVersions(QString(":/").append(rootdirname));
    QStringList lstDirs = resFolderWithVersions.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);

    foreach (QString tempDir, lstDirs)
    {
        QDir subDirs (resFolderWithVersions.absoluteFilePath(tempDir));
        QStringList lstSubDirs = subDirs.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
        foreach (QString tempSubDir, lstSubDirs)
        {
            QString tempPath;
            tempPath.append(rootdirname);
            tempPath.append(QString("/"));
            tempPath.append(tempDir);
            tempPath.append(QString("/"));
            tempPath.append(tempSubDir);
            QDir tempMkDir ("./");
            tempMkDir.mkpath(tempPath);
            QString tempPathRes (":/");
            tempPathRes.append(rootdirname);
            tempPathRes.append("/");
            tempPathRes.append(tempDir);
            tempPathRes.append(QString("/"));
            tempPathRes.append(tempSubDir);
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

void VersionControllerTest::loadDataVersionController()
{
    QTest::addColumn<QStringList>("versions");
    QTest::addColumn<QString>("pathFolder");

    QStringList rootFolderListFolder = rootFolderWithVersions->entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach (QString tempPathFolder, rootFolderListFolder)
    {
        QStringList versionsList = QDir(rootFolderWithVersions->absoluteFilePath(tempPathFolder)).entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
        char *tempappName = QByteArray(tempPathFolder.toLatin1()).data();
        QTest::newRow(tempappName) << versionsList << rootFolderWithVersions->absoluteFilePath(tempPathFolder);
    }
}

int VersionControllerTest::removeFolder(QDir &dir)
{
    int res = 0;
    QStringList lstDirs = dir.entryList(QDir::Dirs |
                                        QDir::AllDirs |
                                        QDir::NoDotAndDotDot);
    QStringList lstFiles = dir.entryList(QDir::Files);

    foreach (QString entry, lstFiles)
    {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
        QFile::remove(entryAbsPath);
    }

    foreach (QString entry, lstDirs)
    {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        QDir dr(entryAbsPath);
        removeFolder(dr);
    }

    if (!QDir().rmdir(dir.absolutePath()))
    {
        res = 1;
    }
    return res;
}

void VersionControllerTest::cleanupTestCase()
{
    removeFolder(*rootFolderWithVersions);
}

void VersionControllerTest::test_getListVersion_data()
{
    loadDataVersionController ();
}

void VersionControllerTest::test_getListVersion()
{
    QFETCH (QStringList,versions);
    QFETCH (QString,pathFolder);
    NetworkMock *network = new NetworkMock (true);
    QString appName = versionData::randomString();
    qDebug () << "app name:     " << appName;
    QDir folderWithVersions (pathFolder);
    VersionController *verCon = new VersionController (folderWithVersions,*network,appName);
    QStringList verListVerCon = verCon->getListVersionStrList();
    QList <AbstractVersion*> verAbList;
    foreach (QString verName, versions)
    {
        AbstractVersion *ver = new VersionNoInstall (appName,verName);
        verAbList.operator <<(ver);
    }
    QStringList verListResult;
    foreach (AbstractVersion *aver, VersionController::sortVersionList(verAbList))
    {
        verListResult << aver->getFullName();
    }
    QCOMPARE (verListVerCon,verListResult);
}

void VersionControllerTest::test_getListInsallVersion()
{

}

void VersionControllerTest::test_getListNoInstallVersion()
{

}

void VersionControllerTest::test_getVersion_data()
{

}

void VersionControllerTest::test_getVersion()
{

}

void VersionControllerTest::test_deleteAllVersion()
{

}

void VersionControllerTest::test_updateVersionsList()
{

}

void VersionControllerTest::test_downloadVersion()
{

}

void VersionControllerTest::test_isFoundVersions()
{

}
