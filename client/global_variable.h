#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>
#include <QWidget>

const unsigned short number_version_launcher = 5;
const QString IPServer = "192.168.1.17";
const unsigned short PortServer = 1234;

enum versionType
{
    pre_alpha,
    alpha,
    beta,
    release,
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
