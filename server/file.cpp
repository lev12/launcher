#include "file.h"

File::File(QString AppName)
{
    nameApp = AppName;
    QString path = ".//data/";
    path.append(AppName);
    dirVer = new QDir(path);
    dirVer->mkdir(path);
    FillingVersionList();
}

void File::FillingVersionList ()
{
    //QDir dir(".//data");
    QList<QFileInfo> temp;
    temp = dirVer->entryInfoList();


    temp.takeAt(0);
    temp.takeAt(0);

    if (!temp.length() == 0)
    {
        int rem_index(0);
        for (int i(0); i < temp.length(); i++)
        {

            if(!temp.at(i-rem_index).isDir())
            {

                temp.takeAt(i-rem_index);
                rem_index++;


            }else
            {
                if(!checkVersion(temp.at(i-rem_index)))
                {
                    temp.takeAt(i-rem_index);
                    rem_index++;
                }

            }
        }
    }

    versions = temp;
    return;
}

bool File::checkVersion(QFileInfo path)
{
/*    QDir dir;
    QString temp_path_ini = path.absoluteFilePath();
    temp_path_ini.append("/data version.ini");
    QFile cfile(temp_path_ini);
    cfile.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&cfile);
    QString temp;
    QString temp_path = path.absolutePath();

    for (int i(0); i<2; i++)
    {
        stream.operator >>(temp);

        switch (i)
        {
        case 0:
            if(temp == "pre-alpha")
            {
              break;
            }
            if(temp == "alpha")
            {
              break;
            }
            if(temp == "beta")
            {
              break;
            }
            if(temp == "release")
            {
              break;
            }
            return false;
            break;

        case 1:
            break;
        case 2:
            temp_path.append(temp);
            if(!dir.cd (temp_path))
            {
                return false;
            }

            break;
        default:
            break;
        }
    }

    return true;*/

    if (path.isFile())
    {
        return false;
    }

    QString pathToConfigVersion = path.absoluteFilePath();
    pathToConfigVersion.append("/data version.ini");
    QFile confIni (pathToConfigVersion);
    if (!(confIni.open(QFile::ReadOnly | QFile::Text)))
    {
        return false;
    }

    QStringList data;
    data = QString (confIni.readAll()).split(" ");

    if (data.at(0) == "pre-alpha"
     || data.at(0) == "alpha"
     || data.at(0) == "beta"
     || data.at(0) == "release")
    {
        if (QString(data.at(1)).toInt() != 0)
        {
            QString pathToExe = path.absoluteFilePath();
            pathToExe.append("/");
            pathToExe.append(data.at(2));
            QFile exe (pathToExe);
            if (exe.exists())
            {
                return true;
            }
        }
    }

    return false;
}

bool File::checkVersion(QString type, QString number)
{
    QString nameVesion;
    if (type != "null")
    {
        nameVesion = type;
        nameVesion.append(" ");
    }
    nameVesion.append(number);

    for (int i(0);i < versions.length();i++)
    {
        if(nameVesion == getVersionName(versions.at(i)))
        {
            return true;
        }
    }

    return false;
}

QFileInfo File::getFile (QString type, QString number)
{
    QFileInfo temp;
    QString name;
    if (type != "null")
    {
        name = type;
        name.append(" ");
    }
    name.append(number);
    qDebug () << name;

    for (int i(0);i < versions.length();i++)
    {
        if(name == versions.at(i).baseName())
        {
            temp = versions.at(i);
            return temp;
        }
    }

    return temp;
}

QList<QFileInfo> File::getVersonsList()
{
    FillingVersionList();
    return versions;
}

QString File::getVersionName (QFileInfo path)
{
    QString result;
    QString temp;
    QString FullPath = path.absoluteFilePath();
    FullPath.append("/data version.ini");
    QFile file(FullPath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);

    stream.operator >> (result);
    result.append(" ");
    stream.operator >> (temp);
    result.append(temp);

    return result;
}

QString File::getExeFile (QFileInfo path)
{
    QString result;
    QString temp;
    QString FullPath = path.absoluteFilePath();
    FullPath.append("/data version.ini");
    QFile file(FullPath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);

    stream.operator >>(temp);
    stream.operator >>(temp);
    stream.operator >>(result);

    return result;
}

QString File::getAppName() const
{
    return QString(nameApp);
}
