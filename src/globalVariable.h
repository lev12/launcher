#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>
#include <QDir>
#include "config.h"
#include "log.h"
#include "versionType.h"
#include "platformType.h"
#include "network/networkKeys.h"

Q_DECLARE_METATYPE (QDir)
const float number_version_launcher = 1.0;
static Config cfgLauncher = Config(".\\conf.cfg");
static Log logLauncher = Log (QString(".\\log"));
const QString _Data = "data/";
static QString serverDomain = "electrical-simulator.ru";

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
