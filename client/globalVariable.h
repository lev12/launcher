#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>
#include "config.h"
#include "log.h"
#include "versionType.h"

const float number_version_launcher = 1.0;
static Config cfgLauncher = Config(".\\conf.cfg");
const QString _Data = "data/";
static QString serverDomain = "electrical-simulator.ru";

struct NetworkData
{
    QString key;
    QString value;
};

enum Language
{
    Chinese,
    Spanish,
    English,
    Arab,
    Portuguese,
    Bengal,
    Russian,
    Japanese,
    German,
    Korean,
    French,
    Turkish,
    Italian,
    Malay,
    Persian,
    Dutch
};

enum Platform
{
    PC,
    MAC,
    Android,
    IOS,
    XBox,
    PlayStation
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
