#include "application.h"

Application::Application()
{

}

void Application::connectServer()
{
    getlistversion ();
    return;
}

void Application::getlistversion()
{
    getListVersions();
    QObject::connect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
}

void Application::downloadversion()
{

    pbHb->addWidget(progressBar);
    progressBar->setStyleSheet("color: rgb(255, 255, 255);\nbackground-color: rgb(41, 90, 108);");
    downloadVersion();
    QStringList name = getItemComboBox().split(" ");
    versionType type;
    QString typeStr = name.at(0);

    if      (typeStr == "pre-alpha") type = pre_alpha;
    else if (typeStr == "alpha")     type = alpha;
    else if (typeStr == "beta")      type = beta;
    else if (typeStr == "release")   type = release;

    network->downloadVersion(appName,type,QString (name.at(1)).toInt());
    QObject::connect(network, SIGNAL(downloadFileEnd()), this, SLOT(endDownloadFile()));
}

void Application::endDownloadFile()
{
    refresh();
    fillingComboBox();
}

void Application::listVersion()
{
    versionsNetwork = network->listVersion;
    QObject::disconnect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
    fillingComboBox();
}

void Application::updateDownload()
{
    static int i;
    i++;
    qDebug () << "upDwlo";
    progressBar->setRange(0,100);
    progressBar->setValue(i/network->countFiles*100);
}

void Application::updateButton()
{
    if (getItemComboBox() == "")
    {
        return;
    }
    QString item = getItemComboBox();
    if (isInstall(item.split(" ").at(0), item.split(" ").at(1)))
    {
        startButton->setText("start");
    }
    else
    {
        startButton->setText("download");
    }
}

void Application::init(Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton, QHBoxLayout *pb)
{
    comboBox = cb;
    startButton = StartButton;
    pbHb = pb;
    appName = AppName;
    network = netWork;

    progressBar = new QProgressBar ();

    fillingComboBox();
    initFiles(appName);

    QObject::connect(network, SIGNAL (connectServer()), this, SLOT (connectServer()));
    QObject::connect(this, SIGNAL (getListVersions ()), network, SLOT (getVersionListOnServer (QString)));
    network->getVersionListOnServer(appName);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(open()));
    QObject::connect(this, SIGNAL (downloadVersion ()), network, SLOT(downloadVersion(QString,versionType,int)));
    QObject::connect(network, SIGNAL(downloadFileEnd()), this, SLOT(endDownloadFile()));
    QObject::connect(network, SIGNAL(downloadFile()), this, SLOT(updateDownload()));

    return;
}

void Application::openFolder()
{
    QString pathToFolder = ".//data/";
    pathToFolder.append(appName);
    QFileInfo file (pathToFolder);

    QDesktopServices::openUrl(QUrl::fromLocalFile(file.absoluteFilePath()));
}

void Application::refresh()
{
    refreshFiles();
    fillingComboBox();
}

void Application::fillingComboBox()
{
    comboBox->clear();
    if (versionsNetwork.length() == 0)
    {
        qDebug () << "offline";
        for (int i(0); i < versionsInstalled.length(); i++)
        {
            comboBox->addItem(QIcon(":/icon/folder.png"),versionsInstalled.at(i).baseName());
        }
    }
    else
    {
        qDebug () << "online";
        QStringList tempListVersions;

        for (int i(0); i < versionsInstalled.length(); i++)
        {
            tempListVersions << versionsInstalled.at(i).baseName();
            qDebug () << i << versionsInstalled.at(i).baseName();
        }

        for (int i(0); i < versionsNetwork.length(); i++)
        {
            bool isItem = false;
            for (int a(0); a < tempListVersions.length(); a++)
            {
                if (versionsNetwork.at(i) == tempListVersions.at(a))
                {
                    isItem = true;
                    break;
                }
            }

            if (!isItem)
            {
                qDebug () << i << versionsNetwork.at(i);
                tempListVersions << versionsNetwork.at(i);
            }
        }

        for (int i(0); i < tempListVersions.length(); i++)
        {
            QIcon *icon;
            QString tempItem = tempListVersions.at(i);
            comboBox->addItem(tempItem);
            if (isInstall(tempItem.split(" ").at(0),tempItem.split(" ").at(1)))
            {
                icon = new QIcon (":/icon/folder.png");
            }
            else
            {
                icon = new QIcon (":/icon/download.png");
            }
            comboBox->setItemIcon(i,*icon);
        }
    }
    QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButton()));
}

QString Application::getItemComboBox()
{
    return comboBox->currentText();
}

void Application::open()
{
    QStringList tempItem = getItemComboBox().split(" ");
    if (checkVersion(tempItem.at(0),tempItem.at(1)))
    {
        QString pathToExe = ".//data/";
        pathToExe.append(tempItem.at(0)); pathToExe.append(" ");
        pathToExe.append(tempItem.at(1)); pathToExe.append("/");
        pathToExe.append(getExeFile(getFile(tempItem.at(0),tempItem.at(1))));

        QStringList arguments;
        arguments << "-style" << "fusion";
        QProcess::startDetached(pathToExe,arguments);
    }
    else
    {
        downloadversion();
    }
}
