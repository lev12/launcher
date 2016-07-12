#include "config.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

config::config()
{
   QFile conf();
   if (!QFile::exists(".\\conf.cfg"))
   {
       create();
   }
   else
   {
       refresh();
   }
}

void config::init()
{
    data.height = 800;
    data.str_height = "height";
    data.width = 600;
    data.str_width = "width";
}

bool config::create()
{
    init();

    QFile cFile(".//conf.cfg");
    if (!(cFile.open(QFile::WriteOnly | QFile::Text))) {
        return false;
    }

    QTextStream stream(&cFile);

    stream << data.str_height << " " << data.height << "\n";
    stream << data.str_width  << " " << data.width << "\n";
    cFile.close();
    return true;
}

bool config::refresh()
{
    QFile cFile(".//conf.cfg");

    if (!cFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QTextStream stream(&cFile);

    bool ok;
    QString buffer[6];
    for (int i(0); i<6; i++)
    {
        stream.operator >> (buffer[i]);

        switch (i) {
        case 0:
            data.str_height = buffer[i];
        case 1:
            data.height = buffer[i].toInt(&ok, 10);
        case 2:
            data.str_width = buffer[i];
        case 3:
            data.width = buffer[i].toInt(&ok, 10);
        default:
            break;
        }
    }
    cFile.flush();
    cFile.close();
    return true;
}

int config::get (QString str)
{
    if (str == "height")
    {
        return data.height;
    }
    if (str == "width")
    {
        return data.width;
    }

    return false;
}
