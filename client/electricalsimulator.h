#ifndef ELECTRICALSIMULATOR_H
#define ELECTRICALSIMULATOR_H

#include <QFrame>
#include "global_variable.h"

namespace Ui {
class ElectricalSimulator;
}

class ElectricalSimulator : public QFrame
{
    Q_OBJECT

public:
    explicit ElectricalSimulator(QWidget *parent = 0);
    ~ElectricalSimulator();

    virtual appInfo getAppInfo ();
private:
    Ui::ElectricalSimulator *ui;
    appInfo appinfo;
};

#endif // ELECTRICALSIMULATOR_H
