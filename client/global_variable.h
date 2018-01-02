#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>
#include <QWidget>
#include "config.h"
#include "log.h"

const float number_version_launcher = 1.0;
const QString IPServer = "192.168.1.15";
const unsigned short PortServer = 1234;
const QString _Host = "http://electrical-simulator.ru/";

enum versionType
{
    pre_alpha,
    alpha,
    beta,
    release,
    Null
};

struct appInfo
{
    short int page;
    QWidget *widget;
    QString nameApp;
    QString webSite;
    QString vk;
    QString youtube;
};

#endif // GLOBAL_VARIABLE_H
