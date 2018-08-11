#include "networkTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qRegisterMetaType<QList<NetworkData>*>("QList<NetworkData>*");
    NetworkTest *testNetwork = new NetworkTest ();
    QTest::qExec (testNetwork,argc, argv);
}
