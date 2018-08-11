#ifndef VERSIONVONTROLLERTEST_H
#define VERSIONVONTROLLERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "versionController.h"
#include "versiondata.h"

class VersionControllerTest : public QObject
{
    Q_OBJECT
public:
    explicit VersionControllerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // VERSIONVONTROLLERTEST_H
