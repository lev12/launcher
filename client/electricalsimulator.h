#ifndef ELECTRICALSIMULATOR_H
#define ELECTRICALSIMULATOR_H

#include <QFrame>
#include "global_variable.h"
#include "files.h"
#include "application.h"
#include "network.h"

namespace Ui {
class ElectricalSimulator;
}

class ElectricalSimulator : public Application
{
    Q_OBJECT

public:
    explicit ElectricalSimulator(Network *net);
    ~ElectricalSimulator();

    virtual appInfo getAppInfo ();
private:
    Ui::ElectricalSimulator *ui;
    appInfo appinfo;
};

#endif // ELECTRICALSIMULATOR_H
