#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(Network *net) :
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(deactiveButton()), this, SLOT(deactiveButton()));
    QObject::connect(net, SIGNAL(downloadFileEnd()), this, SLOT(activeButton()));

    appinfo.page = 1;
    appinfo.nameApp = "Electrical Simulator";
    appinfo.vk = "http://vk.com";
    appinfo.youtube = "http://youtude.com";
    appinfo.webSite = "http://electrical-simulator.ru/";
    appinfo.widget = this;

    init(net, appinfo, ui->comboBox, ui->start, ui->horizontalLayout_for_progressBar);
}

ElectricalSimulator::~ElectricalSimulator()
{
    delete ui;
}

appInfo ElectricalSimulator::getAppInfo ()
{
    return appinfo;
}

void ElectricalSimulator::on_refresh_clicked()
{
    refresh(true);
}

void ElectricalSimulator::on_pushButton_openFolder_clicked()
{
    openFolder();
}

void ElectricalSimulator::on_pushButton_versionManager_clicked()
{
    openVersionManager(ui->horizontalLayout_versionManager);
}

void ElectricalSimulator::deactiveButton()
{
    ui->refresh->setEnabled(false);
    ui->pushButton_versionManager->setEnabled(false);
    ui->start->setEnabled(false);
}

void ElectricalSimulator::activeButton()
{
    ui->refresh->setEnabled(true);
    ui->pushButton_versionManager->setEnabled(true);
    ui->start->setEnabled(true);
}
