#include "versionNoInstallTest.h"
#include "versionInstallTest.h"
#include "abstractVersionTest.h"
#include "versionControllerTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    VersionNoInstallTest *testNIVer = new VersionNoInstallTest ();
    QTest::qExec (testNIVer,argc, argv);
    VersionInstallTest *testIVer = new VersionInstallTest ();
    QTest::qExec (testIVer,argc, argv);
    AbstractVersionTest *testAVer = new AbstractVersionTest ();
    QTest::qExec (testAVer,argc, argv);
    VersionControllerTest *testVerCon = new VersionControllerTest ();
    QTest::qExec (testVerCon,argc, argv);
}
