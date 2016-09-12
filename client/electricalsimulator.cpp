#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(Network *net) :
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);
    init(net, "ElectricalSimulator", ui->comboBox, ui->start);

}

ElectricalSimulator::~ElectricalSimulator()
{
    delete ui;
}

appInfo ElectricalSimulator::getAppInfo ()
{
    return appinfo;
}
