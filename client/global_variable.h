#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QString>


const unsigned short number_version_launcher = 5;
const QString IPServer = "192.168.1.12";
const unsigned short PortServer = 1234;

enum versionType
{
    pre_alpha,
    alpha,
    beta,
    release,
};

#endif // GLOBAL_VARIABLE_H
