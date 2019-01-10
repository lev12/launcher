#include "versionException.h"

VersionException::VersionException(int &code,AbstractVersion *ever, QString estr) : Exception (),
    exceptionVersion (ever)
{

}

AbstractVersion *VersionException::getVersion()
{
    return exceptionVersion;
}

QString VersionException::getExceptionString(int code, QString &estr,QString &verName)
{
    QString errorString (QString::number(code));
    errorString.append(" ");
    errorString.append(verName);
    errorString.append(" ");
    errorString.append(estr);
    return errorString;
}
