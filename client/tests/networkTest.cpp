#include "networkTest.h"

NetworkTest::NetworkTest()
{

}

void NetworkTest::initTestCase()
{
    cfg = new Config (":/versionTestData/launcher config.cfg");
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
}

void NetworkTest::cleanupTestCase()
{

}

void NetworkTest::test_getActualVersion()
{
    QString appName = "Electrical_Simulator";
    qDebug () << "app name:     " << appName;
    Network *net = new Network (*addressServer,*portServer);
    AbstractRequest *request = net->getActualVersion(appName);
    connect(request,AbstractRequest::replyServer,this,recive_getActualVersion);
}

void NetworkTest::test_getVersionList()
{

}

void NetworkTest::test_getFileList()
{

}

void NetworkTest::test_getCheckVersion()
{

}

void NetworkTest::test_getVersion()
{

}

void NetworkTest::test_getFile()
{

}

void NetworkTest::test_getVerInfo()
{

}

void NetworkTest::test_getAppInfo()
{

}

void NetworkTest::recive_getActualVersion(QList<NetworkData> *response)
{

}
