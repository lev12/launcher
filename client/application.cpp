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
    downloadVersion();
    QObject::connect(network, SIGNAL(downloadFileEnd()), this, SLOT(endDownloadFile()));
}

void Application::endDownloadFile()
{

}

void Application::listVersion()
{
    versionsNetwork = network->listVersion;
    qDebug () << versionsNetwork.length();
    QObject::disconnect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
    fillingComboBox();
}

void Application::init(Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton)
{
    comboBox = cb;
    startButton = StartButton;
    appName = AppName;
    network = netWork;

    QObject::connect(network, SIGNAL (connectServer()), this, SLOT (connectServer()));
    QObject::connect(this, SIGNAL (getListVersions ()), network, SLOT (getVersionListOnServer (QString)));
    network->getVersionListOnServer(appName);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(open()));
    QObject::connect(this, SIGNAL (downloadVersion ()), network, SLOT(downloadVersion(QString,versionType,int)));

    return;
}

void Application::fillingComboBox()
{
    QStringList tempListVersions;

    for (int i(0); i < versionsInstalled.length(); i++)
    {
        tempListVersions << versionsInstalled.at(i).baseName();
        qDebug () << i << versionsInstalled.at(i).baseName();
    }

    for (int i(0); i < versionsNetwork.length(); i++)
    {
        int numberItem;
        bool isItem = false;
        for (int a(0); a < tempListVersions.length(); a++)
        {
            numberItem = a;
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
        QIcon icon();
        QString tempItem = tempListVersions.at(i);
        comboBox->addItem(tempItem);
        if (isInstall(tempItem.split(" ").at(0),tempItem.split(" ").at(1)))
        {
            qDebug () << "ass";
        }
    }
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
        //TODO open
    }
    else
    {
        downloadversion();
    }
}
