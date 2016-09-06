#include "files.h"

Files::Files()
{
    QDir dir (".//");
    dir.mkdir("data");

    QList <QFileInfo> tempFileList = dir.entryInfoList();

    if (!tempFileList.length() == 0)
    {
        int rem_index = 0;
        for (int i(0); i<=(tempFileList.length()+1); i++)
        {
            if(!tempFileList.at(i-rem_index).isDir())
            {
                tempFileList.takeAt(i-rem_index);
                rem_index++;
            }
            else
            {
                if(!checkVersion(tempFileList.at(i-rem_index)))
                {
                    tempFileList.takeAt(i-rem_index);
                    rem_index++;
                }
            }
        }
    }
    versionsInstalled = tempFileList;
}

bool Files::checkVersion(QFileInfo path)
{
    QDir dir (".//");
    QString temp_path_ini = path.absoluteFilePath();
    temp_path_ini.append("/data version.ini");
    QFile cfile(temp_path_ini);
    cfile.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&cfile);
    QString temp;
    QString temp_path = path.absolutePath();

    for (int i(0); i<2; i++)
    { //TODO
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

    return true;
}

bool Files::checkVersion(QString type, QString number)
{
    QString nameVesion = type;
    nameVesion.append(" ");
    nameVesion.append(number);

    for (int i(0);i < versionsInstalled.length();i++)
    {
        if(nameVesion == getVersionName(versionsInstalled.at(i)))
        {
            return true;
        }
    }

    return false;
}

QString Files::getVersionName (QFileInfo path)
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

QString Files::getExeFile(QFileInfo path)
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

QFileInfo Files::getFile(QString type, QString number)
{
    QFileInfo temp;
    QString name = type;
    name.append(" ");
    name.append(number);

    for (int i(0); versionsInstalled.length() > i+1;i++)
    {
        if(name == versionsInstalled.at(i).baseName())
        {
            temp = versionsInstalled.at(i);
            return temp;
        }
    }

    return temp;
}

bool Files::isInstall(QString type, QString number)
{
    bool install;
    QString name = type; name.append(" "); name.append(number);
    for (int i(0); i < versionsInstalled.length(); i++)
    {
        if (getVersionName(versionsInstalled.at(i)) == name)
        {
            install = true;
            break;
        }
    }
    return install;
}

bool Files::deleteVersion(QString type, QString number)
{
    if(!checkVersion(type,number))
    {
        return false;
    }

    QString name = getVersionName(getFile(type,number));

    QString path = ".//data/";
            path.append(name);
    QDir dirDel(path);

    removeFolder(dirDel);


    return true;
}

int Files::removeFolder(QDir &dir)
{
    int res = 0;
    QStringList lstDirs = dir.entryList(QDir::Dirs |
                    QDir::AllDirs |
                    QDir::NoDotAndDotDot);
    QStringList lstFiles = dir.entryList(QDir::Files);

    foreach (QString entry, lstFiles)
    {
     QString entryAbsPath = dir.absolutePath() + "/" + entry;
     QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
     QFile::remove(entryAbsPath);
    }

    foreach (QString entry, lstDirs)
    {
     QString entryAbsPath = dir.absolutePath() + "/" + entry;
     QDir dr(entryAbsPath);
     removeFolder(dr);
    }

    if (!QDir().rmdir(dir.absolutePath()))
    {
      res = 1;
    }
    return res;
}
