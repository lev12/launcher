#include "config.h"

#include <QMessageBox>
#include <QTextStream>

config::config()
{
   name = new QStringList();
   argumet = new QStringList();

   if (!QFile::exists(".\\conf.cfg"))
   {
       create();
   }
   else
   {
       raedFile();
   }
}

config::~config()
{
    save();
}

void config::setDefaltParametr()
{
    QFile defParam(":/other/configDefaltParametr.txt");
    if(!(defParam.open(QFile::ReadOnly | QFile::Text)))
    {
        return;
    }

    QTextStream stream (&defParam);

    for (int i(0); i < 10; i++)
    {
        if (i%2 == 0)
        {
            QString temp;
            stream >> temp;
            name->operator <<(temp);
        }
        else
        {
            QString temp;
            stream >> temp;
            argumet->operator <<(temp);
        }
    }
}

bool config::create()
{
    setDefaltParametr();

    QFile cFile(".//conf.cfg");
    if (!(cFile.open(QFile::WriteOnly | QFile::Text))) {
        return false;
    }

    QTextStream stream(&cFile);

    for (int i(0); i < name->count(); i++)
    {
        stream << name->at(i) << " " << argumet->at(i) << "\n";
    }

    cFile.flush();
    cFile.close();
    return true;
}

bool config::raedFile()
{
    QFile cFile(".//conf.cfg");

    if (!cFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QTextStream stream(&cFile);

    for (int i(0); i < 10; i++)
    {
        if (i%2 == 0)
        {
            QString temp;
            stream >> temp;
            name->operator <<(temp);
        }
        else
        {
            QString temp;
            stream >> temp;
            argumet->operator <<(temp);
        }
    }

    cFile.flush();
    cFile.close();
    return true;
}

bool config::save()
{
    QFile cFile(".//conf.cfg");
    cFile.remove();
    if (!cFile.open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }

    QTextStream stream(&cFile);

    for (int i(0); i < 10; i++)
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
    }

    cFile.flush();
    cFile.close();
    return true;
}

QString config::get(QString parametr)
{
    int number = -1;

    for (int i(0); i < name->count(); i++)
    {
        if (parametr == name->at(i))
        {
            number = i;
            break;
        }
    }

    if (number == -1) return false;

    QString result = argumet->at(number);
    return result;
}

bool config::set(QString parametr, QString value)
{
    int number = -1;
    for (int i(0); i < name->count(); i++)
    {
        if (parametr == name->at(i))
        {
            number = i;
            break;
        }
    }
    if (number == -1) return false;

    argumet->replace(number, value);

    return true;
}
