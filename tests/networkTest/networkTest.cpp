#include "networkTest.h"

NetworkTest::NetworkTest()
{

}

void NetworkTest::loadApplicationData(QList<metaApplication *> *metaAppData)
{
    QTest::addColumn<QString>("applicationName");

    foreach (metaApplication* tempapp, *metaAppData)
    {
        char *tempappName = QByteArray(tempapp->app.toLatin1()).data();
        QTest::newRow(tempappName) << tempapp->app;
    }
}

void NetworkTest::loadVersionData(QList <metaApplication*> *metaAppData)
{
    QTest::addColumn<QString>("applicationName");
    QTest::addColumn<QString>("versionName");

    foreach (metaApplication *tempapp,*metaAppData)
    {
        foreach (QString tempver,tempapp->ver)
        {
            QString tempCaseName = tempapp->app;
            tempCaseName.append("_");
            tempCaseName.append(tempver);
            char *tempappName = QByteArray(tempCaseName.toLatin1()).data();
            QTest::newRow(tempappName) << tempapp->app << tempver;
        }
    }
}

void NetworkTest::loadFileData(QList<metaApplication *> *metaAppData)
{
    QTest::addColumn<QString>("applicationName");
    QTest::addColumn<QString>("versionName");
    QTest::addColumn<QString>("fileRelPath");


    foreach (metaApplication *tempapp,*metaAppData)
    {
        foreach (QString tempver,tempapp->ver)
        {
            foreach (QString tempfile,tempapp->files)
            {
                QString tempCaseName = tempapp->app;
                tempCaseName.append("_");
                tempCaseName.append(tempver);
                tempCaseName.append("_");
                tempCaseName.append(tempfile);
                char *tempappName = QByteArray(tempCaseName.toLatin1()).data();
                QTest::newRow(tempappName) << tempapp->app << tempver << tempfile;
            }
        }
    }
}

void NetworkTest::initTestCase()
{
    appList = new QList <metaApplication*>;
    QDir (".//").mkdir(".//networkData");
    dataFolder = new QDir (".//networkData");
    
    cfg = new Config (":/launcher config.cfg");
    QString tempAddressServer = cfg->get("DomainServer").at(0);
    if (Config::isError(tempAddressServer))
    {
        QFAIL ("not found \"DomainServer\" in config file \":/versionTestData/launcher config.cfg\"");
    }
    QString tempPortServer = cfg->get("PortServer").at(0);
    if (Config::isError(tempPortServer))
    {
        QFAIL ("not found \"PortServer\" in config file \":/versionTestData/launcher config.cfg\"");
    }
    addressServer = new QString(tempAddressServer);
    portServer = new quint16;
    bool isConvertToUShort;
    *portServer = tempPortServer.toUShort(&isConvertToUShort);
    if (!isConvertToUShort)
    {
        QFAIL ("PortServer no convet to ushort");
    };
    qDebug () << "port:" << *portServer;
    qDebug () << "address:" << *addressServer;
    network = new Network (*addressServer,*portServer);
}

void NetworkTest::cleanupTestCase()
{
    dataFolder->removeRecursively();
}

void NetworkTest::test_getApplicationList()
{
    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getApplicationList();

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    foreach (NetworkData tempApplication, *response)
    {
        metaApplication *tempMetaApp = new metaApplication;
        tempMetaApp->app = tempApplication.value.toString();
        appList->operator <<(tempMetaApp);
    }
}

void NetworkTest::test_getVersionList_data()
{
    loadApplicationData(appList);
}

void NetworkTest::test_getVersionList()
{
    QFETCH (QString,applicationName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getVersionList(AbstractRequest::spaceTo_(applicationName));

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    qDebug () << response->at(0).value;
    QCOMPARE(response->at(0).key,QString("versionList"));
    
    QStringList tempVersionList;
    foreach (NetworkData tempVersion, *response)
    {
        tempVersionList << tempVersion.value.toString();
    }
    foreach (metaApplication *tempMetaApp, *appList)
    {
        if (tempMetaApp->app == applicationName)
        {
            tempMetaApp->ver = tempVersionList;
        }
    }
}

void NetworkTest::test_getActualVersion_data()
{
    loadApplicationData(appList);
}

void NetworkTest::test_getActualVersion()
{
    QFETCH (QString,applicationName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getActualVersion(AbstractRequest::spaceTo_(applicationName));

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    qDebug () << response->count();
    qDebug () << response->at(0).value;
    QCOMPARE(response->at(0).key,QString("actualVersion"));
}

void NetworkTest::test_getFileList_data()
{
    loadVersionData(appList);
}

void NetworkTest::test_getFileList()
{
    QFETCH (QString,applicationName);
    QFETCH (QString,versionName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getFileListVersion(AbstractRequest::spaceTo_(applicationName),versionName);

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    for (int i(0);i < response->length();i++)
    {
        QCOMPARE(response->at(i).key.toInt(),i);
    }

    QStringList tempFilesList;
    foreach (NetworkData tempFile, *response)
    {
        tempFilesList << tempFile.value.toString();
    }
    foreach (metaApplication *tempMetaApp, *appList)
    {
        if (tempMetaApp->app == applicationName)
        {
            foreach (QString tempver, tempMetaApp->ver)
            {
                if(tempver == versionName)
                {
                    tempMetaApp->files = tempFilesList;
                }
            }
        }
    }
}

void NetworkTest::test_getCheckVersion_data()
{
    loadVersionData(appList);
}

void NetworkTest::test_getCheckVersion()
{
    QFETCH (QString,applicationName);
    QFETCH (QString,versionName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getCheckVersion(applicationName,versionName);

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    QCOMPARE(response->at(0).value.toBool(),true);
}

void NetworkTest::test_getVersionInfo_data()
{
    loadVersionData(appList);
}

void NetworkTest::test_getVersionInfo()
{
    QFETCH (QString,applicationName);
    QFETCH (QString,versionName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getVersionInfo(applicationName,versionName);

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    foreach (NetworkData tempNetData, *response)
    {
        qDebug () << tempNetData.key << tempNetData.value;
        if (tempNetData.key == QString("Version_Type"))
        {
            bool isType = false;
            if (tempNetData.value.toString() == "null")
            {
                isType = true;
            }
            else
            {
                isType = AbstractVersion::stringToVersionType(tempNetData.value.toString()) != null;
            }
            QVERIFY (isType);
        }
        if (tempNetData.key == QString("Version_Number"))
        {
            bool isNumber;
            tempNetData.value.toInt(&isNumber);
            QVERIFY (isNumber);
        }
        if (tempNetData.key == QString("Start_File"))
        {
            bool isStartFileName = false;
            QString extension = tempNetData.value.toString().split(".").last();
            if (extension == QString ("exe"))
            {
                isStartFileName = true;
            }
            QVERIFY (isStartFileName);
        }
    }
}

void NetworkTest::test_getAppInfo_data()
{
    loadApplicationData(appList);
}

void NetworkTest::test_getAppInfo()
{
    QFETCH (QString,applicationName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    AbstractRequest *request = network->getAppInfo(applicationName);

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

    foreach (NetworkData tempNetData, *response)
    {
        qDebug () << tempNetData.key << tempNetData.value;
        if (tempNetData.key == "name")
        {
            QVERIFY (tempNetData.value.toString() != "");
        }
    }
}

void NetworkTest::test_getFile_data()
{
    loadFileData(appList);
}

void NetworkTest::test_getFile()
{
    QFETCH (QString,applicationName);
    QFETCH (QString,versionName);
    QFETCH (QString,fileRelPath);

    /*QTestEventLoop &loop = QTestEventLoop::instance();

    QString fileDownloadUrlStr("");
    fileDownloadUrlStr += *addressServer;
    fileDownloadUrlStr += ":";
    fileDownloadUrlStr += QString::number(*portServer);
    fileDownloadUrlStr += "/app/";
    fileDownloadUrlStr += AbstractRequest::spaceTo_(applicationName);
    fileDownloadUrlStr += "/";
    fileDownloadUrlStr += AbstractRequest::spaceTo_(versionName);
    fileDownloadUrlStr += "/";
    fileDownloadUrlStr += fileRelPath;
    QUrl fileDownloadUrl (fileDownloadUrlStr);
    qDebug () << fileDownloadUrl;
    QString fileDownloadPath(dataFolder->absolutePath());
    fileDownloadPath += "/";
    fileDownloadPath += AbstractRequest::spaceTo_(applicationName);
    fileDownloadPath += "/";
    fileDownloadPath += AbstractRequest::spaceTo_(versionName);
    fileDownloadPath += "/";
    fileDownloadPath += fileRelPath;
    qDebug () << fileDownloadPath;
    qDebug () << QFileInfo (fileDownloadPath).isFile();
    QFileInfo fileDownload (fileDownloadPath);
    AbstractRequest *request;
    try
    {
        request = network->getFile(fileDownloadUrl,fileDownload);
    }
    catch (char const* error)
    {
        qDebug () << error;
    }

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));

    connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
    loop.enterLoop(30);
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();
    QVERIFY (fileDownload.exists());
    QVERIFY2 (QFile (fileDownload.absoluteFilePath()).remove(),"not deleted file");*/
}

void NetworkTest::test_getVersion_data()
{
    loadVersionData(appList);
}

void NetworkTest::test_getVersion()
{
    QFETCH (QString,applicationName);
    QFETCH (QString,versionName);

    QTestEventLoop &loop = QTestEventLoop::instance();

    QString appNameUnderscope = AbstractRequest::spaceTo_(applicationName);
    QString saveFolderPath (dataFolder->absolutePath());
    saveFolderPath += "/";
    saveFolderPath += AbstractRequest::spaceTo_(applicationName);
    saveFolderPath += "/";
    saveFolderPath += AbstractRequest::spaceTo_(versionName);
    QDir saveFolder (saveFolderPath);

    AbstractRequest *request;
    try
    {
        request = network->getVersion(appNameUnderscope,versionName,saveFolder);
        connect(request,SIGNAL(replyServer(QList<NetworkData>*)),&loop,SLOT(exitLoop()));
        loop.enterLoop(30);
    }
    catch (char const* ex)
    {
        qDebug () << ex;
    }

    QSignalSpy *signalspy;
    signalspy = new QSignalSpy (request,SIGNAL(replyServer(QList<NetworkData>*)));
    QVERIFY (!loop.timeout());

    QVariant netData = signalspy->takeFirst();
    QList<NetworkData>* response = netData.toList().at(0).value<QList<NetworkData>*>();

}
