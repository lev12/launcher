#include "application.h"

Application::Application()
{

}

void Application::connectServer()
{
    getListVersions();
    return;
}

void Application::listVersion()
{
    versions = network->listVersion;
    qDebug () << versions.length();
    FillingComboBox();
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
    QObject::connect(network, SIGNAL(listVersions()), this, SLOT(listVersion()));

    return;
}

void Application::FillingComboBox()
{
    comboBox->addItems(versions);
}
