#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <stdexcept>

class Exception : public std::exception
{
public:
    Exception(int code, QString &estr);
    Exception();
    ~Exception();

    virtual char const* what() const noexcept;
    int* getErrorCode();

private:
    int *codeError;

protected:
    QString *whatString;
    QString getErrorStringWithCode (QString &estr, int &code);
};

#endif // EXCEPTION_H
