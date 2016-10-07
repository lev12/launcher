#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(Network *net) :
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);
    init(net, "Electrical Simulator", ui->comboBox, ui->start, ui->horizontalLayout_for_progressBar);
    //bg = new background(ui->horizontal_widget, ":/icon/background.jpg");
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
