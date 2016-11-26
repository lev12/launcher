#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(Network *net) :
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);
    init(net, "Electrical Simulator", ui->comboBox, ui->start, ui->horizontalLayout_for_progressBar);
    appinfo.page = 1;
    appinfo.nameApp = "Electrical Simulator";
    appinfo.vk = "http://vk.com";
    appinfo.youtube = "http://youtude.com";
    appinfo.webSite = "http://electrical-simulator.ru/";
    appinfo.widget = this;
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
    refresh();
}

void ElectricalSimulator::on_pushButton_openFolder_clicked()
{
    openFolder();
}

void ElectricalSimulator::on_pushButton_versionManager_clicked()
{
    openVersionManager(ui->horizontalLayout_versionManager);
}
