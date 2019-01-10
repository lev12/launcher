#include "exception.h"

Exception::Exception(int code, QString &estr) :
    codeError (&code)
{
    whatString = new QString();
    *whatString = getErrorStringWithCode (estr,code);
}

Exception::Exception()
{

}

Exception::~Exception()
{
    delete codeError;
    delete whatString;
}

char const * Exception::what() const throw()
{
    char *whatstr = whatString->toLatin1().data();
    return whatstr;
}

int *Exception::getErrorCode()
{
    return codeError;
}

QString Exception::getErrorStringWithCode(QString &estr, int &code)
{
    QString result (QString::number(code));
    result.append(" ");
    result.append(estr);
    return result;
}
