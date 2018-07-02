#include "versionInstallTest.h"
#include "versionNoInstallTest.h"
#include "abstractVersionTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    VersionInstallTest *testIVer = new VersionInstallTest ();
    QTest::qExec (testIVer,argc, argv);
    VersionNoInstallTest *testNIVer = new VersionNoInstallTest ();
    QTest::qExec (testNIVer,argc, argv);
    AbstractVersionTest *testAVer = new AbstractVersionTest ();
    QTest::qExec (testAVer,argc, argv);
}
