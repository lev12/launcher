#ifndef VERSIONDATA_H
#define VERSIONDATA_H

#include <QObject>
#include <QtTest/QtTest>
#include <QString>
#include "versionType.h"

class versionData : public QObject
{
    Q_OBJECT
public:
    explicit versionData(QObject *parent = nullptr);
    static void loadVersionNameData ();
    static void loadInstallVersionData ();
    static QString randomString ();
signals:

public slots:
};

#endif // VERSIONDATA_H
