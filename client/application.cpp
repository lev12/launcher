#include "application.h"
#include <QTime>

Application::Application()
{
    showVersionManager = false;
}

void Application::connectServer()
{
    if (network->isDownload == false)
    {
        getlistversion ();
    }
    return;
}

void Application::getlistversion()
{
    getListVersions();
    QObject::connect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
}

void Application::downloadversion(QString typeString, QString number, bool uiOnly)
{
    progressBar = new QProgressBar ();
    pbHb->addWidget(progressBar);
    progressBar->setTextDirection(QProgressBar::BottomToTop);
    progressBar->setStyleSheet("background-color: rgb(255, 164, 37);");
    if (!uiOnly)
    {
        downloadVersion();
        versionType type;
        QString typeStr = typeString;

        if      (typeStr == "pre-alpha") type = pre_alpha;
        else if (typeStr == "alpha")     type = alpha;
        else if (typeStr == "beta")      type = beta;
        else if (typeStr == "release")   type = release;

        network->downloadVersion(app.nameApp,type,number.toInt());
        deactiveButton();
    }
}

void Application::endDownloadFile()
{
    qDebug () << "upDwlo1";
    pbHb->removeWidget(progressBar);
    delete progressBar;
    refresh(true);
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
    qDebug () << "upDwlo" << QTime::currentTime().toString() << (i*100/network->countFiles) << network->countFiles << i;
    progressBar->setRange(0,100);
    progressBar->setValue(i*100/network->countFiles);
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

void Application::init(Network *netWork, appInfo App, QComboBox *cb, QPushButton *StartButton, QHBoxLayout *pb)
{
    comboBox = cb;
    startButton = StartButton;
    pbHb = pb;
    app = App;
    network = netWork;

    initFiles(app.nameApp);

    QObject::connect(network, SIGNAL (connectServer()), this, SLOT (connectServer()));
    QObject::connect(this, SIGNAL (getListVersions ()), network, SLOT (getVersionListOnServer (QString)));
    QObject::connect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
    network->getVersionListOnServer(app.page);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(open()));
    QObject::connect(this, SIGNAL (downloadVersion ()), network, SLOT(downloadVersion(QString,versionType,int)));
    QObject::connect(network, SIGNAL(downloadFileEnd()), this, SLOT(endDownloadFile()));
    QObject::connect(network, SIGNAL(downloadFile()), this, SLOT(updateDownload()));

    if (network->isDownload == true)
    {
        deactiveButton();
        downloadversion(NULL,NULL,true);
        updateDownload();
        refresh(false);
    }
    else
    {
        refresh(true);
    }

    return;
}

void Application::openFolder()
{
    QString pathToFolder = ".//data/";
    pathToFolder.append(app.nameApp);
    QFileInfo file (pathToFolder);

    QDesktopServices::openUrl(QUrl::fromLocalFile(file.absoluteFilePath()));
}

void Application::refresh(bool updateListVersion)
{
    if (updateListVersion == true)
    {
        QObject::connect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));
        network->getVersionListOnServer(app.page);
    }

    refreshFiles();
    fillingComboBox();
    updateButton();
}

void Application::removeVersionManager()
{
    VMHB->removeWidget(versionmanager);
    delete versionmanager;
    showVersionManager = !showVersionManager;
}

void Application::openVersionManager(QHBoxLayout *widget)
{
    VMHB = widget;
    if (!showVersionManager)
    {
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
                tempListVersions << versionsNetwork.at(i);
            }
        }

        versionmanager = new VersionManager(app.nameApp ,sortVersions(tempListVersions), versionsNetwork);
        widget->addWidget(versionmanager);
        QObject::connect(versionmanager, SIGNAL(closeButton()), this, SLOT(removeVersionManager()));
        QObject::connect(versionmanager, SIGNAL(downloadVersion()), this, SLOT(downloadVersionVersionManager()));
        QObject::connect(versionmanager, SIGNAL(deleteVersion()), this, SLOT(deleteVersionVersionManager()));
    }
    else
    {
        widget->removeWidget(versionmanager);
        delete versionmanager;
    }
    showVersionManager = !showVersionManager;
}

void Application::deleteVersionVersionManager ()
{
    QStringList name = versionmanager->currentVersion.split(" ");
    deleteVersion(name.at(0), name.at(1));
    refreshFiles();
    fillingComboBox();

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
            tempListVersions << versionsNetwork.at(i);
        }
    }

    versionmanager->refreshVersionManager(sortVersions(tempListVersions));
}

void Application::downloadVersionVersionManager()
{
    QStringList name = versionmanager->currentVersion.split(" ");
    downloadversion(name.at(0), name.at(1), false);
}

QStringList Application::sortVersions (QStringList versions)
{
    QStringList returnVersionsList;

    QStringList preAlpha;
    QStringList Alpha;
    QStringList Beta;
    QStringList Release;

    for (int i(0); i < versions.length(); i++)
    {
        QString temp = versions.at(i);
        QString type = temp.split(" ").at(0);

        if      (type == "pre-alpha")   preAlpha.operator <<(versions.at(i));
        else if (type == "alpha")       Alpha.operator <<(versions.at(i));
        else if (type == "beta")        Beta.operator <<(versions.at(i));
        else if (type == "release")     Release.operator <<(versions.at(i));
        else
        {
            qDebug () << "error sort versions" << versions.at(i);
        }
    }

    returnVersionsList.operator <<(Release);
    returnVersionsList.operator <<(Beta);
    returnVersionsList.operator <<(Alpha);
    returnVersionsList.operator <<(preAlpha);

    return returnVersionsList;
}

void Application::fillingComboBox()
{
    comboBox->clear();
    if (versionsNetwork.length() == 0)
    {
        qDebug () << "offline";

        QStringList tempVersionsInstallList;

        for (int i(0); i < versionsInstalled.length(); i++)
        {
            tempVersionsInstallList.operator <<(getVersionName(versionsInstalled.at(i)));
        }


        tempVersionsInstallList = sortVersions(tempVersionsInstallList);
        comboBox->addItems(tempVersionsInstallList);
        for (int i(0); i < tempVersionsInstallList.length(); i++)
        {
            comboBox->setItemIcon(i, QIcon(":/icon/diskette.png"));
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
            tempListVersions = sortVersions(tempListVersions);
            QString tempItem = tempListVersions.at(i);
            comboBox->addItem(tempItem);
            if (isInstall(tempItem.split(" ").at(0),tempItem.split(" ").at(1)))
            {
                icon = new QIcon (":/icon/diskette.png");
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
        downloadversion(tempItem.at(0), tempItem.at(1), false);
    }
}
