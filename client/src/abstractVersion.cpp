#include "abstractVersion.h"

AbstractVersion::AbstractVersion() : QObject()
{

}

QString AbstractVersion::getFullName()
{
    QString name;
    QString type = versionTypeToString(*verType);
    QString number = QString::number(*verNumber);

    if (type != "null")
    {
        name.append(type);
        name.append(" ");
    }
    name.append(number);

    return name;
}

int AbstractVersion::getVersionNumber()
{
    return *verNumber;
}

VersionType AbstractVersion::getVersionType()
{
    return *verType;
}

bool AbstractVersion::getIsInstall()
{
    return *verIsInstall;
}

QString AbstractVersion::getAppName()
{
    return *appName;
}

QString AbstractVersion::versionTypeToString (VersionType type)
{
    QString type_str;
    switch (type) {
    case pre_alpha:
        type_str = "pre-alpha";
        break;
    case alpha:
        type_str = "alpha";
        break;
    case beta:
        type_str = "beta";
        break;
    case release:
        type_str = "release";
        break;
    case null:
        type_str = "null";
        break;
    default:
        type_str = "error";
        break;
    }
    return type_str;
}

VersionType AbstractVersion::stringToVersionType (QString str)
{
    VersionType type;
    if (str == "pre_alpha")
    {
        type = pre_alpha;
    }
    else if (str == "pre-alpha")
    {
        type = pre_alpha;
    }
    else if (str == "alpha")
    {
        type = alpha;
    }
    else if (str == "beta")
    {
        type = beta;
    }
    else if (str == "release")
    {
        type = release;
    }
    else
    {
        type = null;
    }

    return type;
}

PlatformType AbstractVersion::stringToPlatform (QString platformStr)
{
    PlatformType resault;
    if (platformStr == "PC") resault = PC;
    else if (platformStr == "MAC") resault = MAC;
    else if (platformStr == "Android") resault = Android;
    else if (platformStr == "IOS") resault = IOS;
    else if (platformStr == "XBox") resault = XBox;
    else if (platformStr == "PlayStation") resault = PlayStation;
    else resault = Null;

    return resault;
}

void AbstractVersion::initIsInatall(bool install)
{
    verIsInstall = new bool;
    *verIsInstall = install;
}

void AbstractVersion::initAppName(QString AppName)
{
    appName = new QString (AppName);
}

bool AbstractVersion::initVerName(QString VerName)
{
    verNumber = new int;
    verType = new VersionType;

    QStringList tempVerNameList;
    tempVerNameList = VerName.split("_");
    if (tempVerNameList.length() > 1 && tempVerNameList.at(0) == "pre" && QString(tempVerNameList.at(1)).remove(5,QString(tempVerNameList.at(1)).length()) == "alpha")
    {
        tempVerNameList.pop_front();
        if (QString(tempVerNameList.at(0)).remove(0,5).length() > 0)
        {
            tempVerNameList.replace(0,QString(tempVerNameList.at(0)).remove(0,5));
        }
        else
        {
            tempVerNameList.pop_front();
        }

        tempVerNameList.push_front("pre-alpha");
    }
    if(tempVerNameList.length() <= 1)
    {
        tempVerNameList = VerName.split(" ");
        if (tempVerNameList.length() <= 1)
        {
            return false;
        }
    }
    bool *okToInt = new bool;
    *verType = stringToVersionType(tempVerNameList.at(0));
    *verNumber = QString(tempVerNameList.at(1)).toInt(okToInt);
    if (*okToInt == true)
    {
        return true;
    }
    return false;
}
