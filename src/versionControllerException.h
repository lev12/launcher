#ifndef VERSIONCONTROLLEREXCEPTION_H
#define VERSIONCONTROLLEREXCEPTION_H

#include <QString>
#include <stdexcept>
#include "exception.h"

class VersionControllerException : public Exception
{
public:
    VersionControllerException(int code, QString estr);

};

#endif // VERSIONCONTROLLEREXCEPTION_H
