#include <QtTest>
#include <QCoreApplication>
#include "versionInstall.h"
#include "versionNoInstall.h"

// add necessary includes here

class testcase : public QObject
{
    Q_OBJECT

public:
    testcase();
    ~testcase();

    VersionNoInstall *verNoIntsall;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testcase::testcase()
{

}

testcase::~testcase()
{

}

void testcase::initTestCase()
{
    verNoIntsall = new VersionNoInstall ("el","alpha_45");
}

void testcase::cleanupTestCase()
{

}

void testcase::test_case1()
{
    QString r = verNoIntsall->getFullName();
    QCOMPARE (r,QString("alpha 45"));
}

QTEST_MAIN(testcase)

#include "tst_testcase.moc"
