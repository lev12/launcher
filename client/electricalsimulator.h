#ifndef ELECTRICALSIMULATOR_H
#define ELECTRICALSIMULATOR_H

#include <QFrame>
#include "global_variable.h"
#include "files.h"
#include "application.h"
#include "network.h"
#include "background.h"

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
private slots:
    void on_refresh_clicked();

    void on_pushButton_openFolder_clicked();

    void on_pushButton_versionManager_clicked();

private:
    Ui::ElectricalSimulator *ui;
    appInfo appinfo;
    background *bg;
};

#endif // ELECTRICALSIMULATOR_H
