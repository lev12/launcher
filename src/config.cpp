#include "config.h"
const QString Config::errorResponse = "false response of read config";

QStringList &Config::getConfigKeyName() const
{
    return *configKeyName;
}

Config::Config(QString path)
{
    configKeyName = new QStringList();
    configKeyValue = new QStringList();

   if (!QFile::exists(path))
   {
       if (!create(path))
       {
           qDebug () << "fail created file" << path;
       }
   }
   else
   {
       configFile = new QFile (path);
       raedFile();
   }
}

Config::~Config()
{
    //save();
}

bool Config::create(QString path)
{
    QDir makeDir;
    makeDir.mkpath(QFileInfo (path).absolutePath());
    QFile cFile(path);
    if (!(cFile.open(QFile::WriteOnly | QFile::Text))) {
        return false;
    }
    configFile = new QFile(QFileInfo(cFile).absoluteFilePath());
    cFile.close();
    return true;
}

bool Config::raedFile()
{
    if (!configFile->open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QStringList configLines = QString(configFile->readAll()).split("\n");


    for (int i=0; i < configLines.length(); i++)
    {
        if (QString(configLines.at(i)).length() > 2)
        {
            QStringList tempConfigLine = QString(configLines.at(i)).split("=");

            if (tempConfigLine.length() == 2)
            {
                QString cfgKey = tempConfigLine.at(0);
                QString cfgValue = tempConfigLine.at(1);
                if (cfgKey.contains(" "))
                {
                    cfgKey.remove(" ");
                }
                if (cfgValue.contains(" "))
                {
                    cfgValue.remove(" ");
                }

                configKeyName->operator <<(cfgKey);
                configKeyValue->operator <<(cfgValue);
            }
        }
    }


    configFile->flush();
    configFile->close();
    return true;
}

bool Config::save()
{
    configFile->open(QFile::WriteOnly);
    qDebug () << configFile->remove();
    if (!configFile->open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }

    for (int i=0; i < configKeyName->length();i++)
    {
        QString line = QString(configKeyName->at(i));
        line.append(" = ");
        line.append(QString(configKeyValue->at(i)));
        line.append("\n");
        configFile->write(line.toLocal8Bit());
    }

    configFile->flush();
    configFile->close();
    return true;
}

QStringList Config::get(QString parametr)
{
    int number = -1;

    for (int i(0); i < configKeyName->count(); i++)
    {
        if (parametr == configKeyName->at(i))
        {
            number = i;
            break;
        }
    }

    if (number == -1) return QStringList(errorResponse);

    QString result = configKeyValue->at(number);
    QStringList resultList = result.split(", ");
    return resultList;
}

bool Config::set(QString parametr, QString value)
{
    configKeyName->push_back(parametr);
    configKeyValue->push_back(value);

    return true;
}

bool Config::set(QString parametr, QStringList value)
{
    configKeyName->push_back(parametr);
    configKeyValue->push_back(value.join(", "));

    return true;
}

bool Config::isEmpty()
{
    if (configKeyName->length() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Config::isError(QString &value)
{
    if (value == errorResponse)
    {
        return true;
    }
    return false;
}

bool Config::clear()
{
    if(configFile->remove())
    {
        qDebug () << "clear remove no";
    }
    configFile->open(QFile::WriteOnly | QFile::Text);
    configFile->close();
    return true;
}
