#include "uielectricalsimulator.h"
#include "ui_uielectricalsimulator.h"

UiElectricalSimulator::UiElectricalSimulator(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiElectricalSimulator)
{
    ui->setupUi(this);
}

UiElectricalSimulator::~UiElectricalSimulator()
{
    delete ui;
}
