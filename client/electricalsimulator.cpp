#include "electricalsimulator.h"
#include "ui_electricalsimulator.h"

ElectricalSimulator::ElectricalSimulator(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ElectricalSimulator)
{
    ui->setupUi(this);


}

ElectricalSimulator::~ElectricalSimulator()
{
    delete ui;
}

appInfo ElectricalSimulator::getAppInfo ()
{
    return appinfo;
}
