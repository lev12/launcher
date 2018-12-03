#ifndef VERSIONEXCEPTION_H
#define VERSIONEXCEPTION_H

#include <stdexcept>
#include "abstractVersion.h"
#include "exception.h"

class VersionException : public Exception
{
public:
    VersionException(int &code, AbstractVersion *ever, QString estr);

    AbstractVersion *getVersion ();
private:
    AbstractVersion *exceptionVersion;
    QString getExceptionString(int code, QString &estr, QString &verName);
};

#endif // VERSIONEXCEPTION_H
