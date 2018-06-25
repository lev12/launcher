#include "config.h"

Config::Config(QString path)
{
   configKeyName = new QStringList();
   configKeyValue = new QStringList();

   if (!QFile::exists(path))
   {
       create(path);
   }
   else
   {
       configFile = new QFile (path);
       raedFile();
   }
}

Config::~Config()
{
    save();
}

bool Config::create(QString path)
{
    QFile cFile(path);
    if (!(cFile.open(QFile::WriteOnly | QFile::Text))) {
        return false;
    }
    configFile = &cFile;
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
    configFile->remove();
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

    if (number == -1) return QStringList("false");

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

void Config::clear()
{
    configFile->remove();
    configFile->open(QFile::WriteOnly | QFile::Text);
    configFile->close();
}
