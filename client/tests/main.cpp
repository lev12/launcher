#include "versionInstallTest.h"
#include "versionNoInstallTest.h"
#include "abstractVersionTest.h"
#include "networkTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qRegisterMetaType<QList<NetworkData>*>("QList<NetworkData>*");
    /*ersionInstallTest *testIVer = new VersionInstallTest ();
    QTest::qExec (testIVer,argc, argv);
    VersionNoInstallTest *testNIVer = new VersionNoInstallTest ();
    QTest::qExec (testNIVer,argc, argv);
    AbstractVersionTest *testAVer = new AbstractVersionTest ();
    QTest::qExec (testAVer,argc, argv);*/
    NetworkTest *testNetwork = new NetworkTest ();
    QTest::qExec (testNetwork,argc, argv);
}
