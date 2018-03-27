#include "config.h"

Config::Config(QString path)
{
   configKeyName = new QStringList();
   configKeyValue = new QStringList();

   if (!QFile::exists(path))
   {
       create(path);
       empty = true;
   }
   else
   {
       configFile = new QFile (path);
       raedFile();
       empty = false;
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

    //if (configLines.length() > 1)
    {
        qDebug () << "545454564asssddddddd";
        for (int i=0; i < configLines.length(); i++)
        {
            if (QString(configLines.at(i)).length() > 2)
            {
                qDebug () << "asssddddddd";
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

                    qDebug () << cfgKey;
                    configKeyName->operator <<(cfgKey);
                    configKeyValue->operator <<(cfgValue);
                }
            }
        }
    }

    configFile->flush();
    configFile->close();
    return true;
}

bool Config::save()
{
    empty = false;
    configFile->remove();
    if (!configFile->open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    qDebug () << configKeyName->length();
    for (int i=0; i < configKeyName->length();i++)
    {
        QString line = QString(configKeyName->at(i));
        line.append(" = ");
        line.append(QString(configKeyValue->at(i)));
        line.append("\n");
        qDebug () << line;
        configFile->write(line.toLocal8Bit());
    }

    /*QTextStream stream(&cFile);

    for (int i(0); i < countLine*2; i++)
    {
        int tempI = 0;
        if (i%2 == 0)
        {
            if (i != 0)
            {
                tempI = qFloor(i/2);
            }
            QString temp = name->at(tempI);
            stream << temp << " ";
        }
        else
        {
            if (i != 0)
            {
                tempI = i/2;
            }
            QString temp = argumet->at(tempI);
            stream << temp << "\n";
        }
    }*/

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
    int number = -1;
    for (int i(0); i < configKeyName->count(); i++)
    {
        if (parametr == configKeyName->at(i))
        {
            number = i;
            break;
        }
    }
    if (number == -1) return false;

    configKeyValue->replace(number, value);

    return true;
}

bool Config::isEmpty()
{
    return empty;
}
