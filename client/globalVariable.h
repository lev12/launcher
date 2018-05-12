#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>
#include <QWidget>
#include "config.h"
#include "log.h"

const float number_version_launcher = 1.0;


const QString _Data = "data/";

enum VersionType
{
    pre_alpha,
    alpha,
    beta,
    release,
    null
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
