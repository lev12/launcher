#ifndef ELECTRICALASSISTANT_H
#define ELECTRICALASSISTANT_H

#include <QFrame>
#include "application.h"

namespace Ui {
class ElectricalAssistant;
}

class ElectricalAssistant : public Application
{
    Q_OBJECT

public:
    explicit ElectricalAssistant(Network *net = 0);
    appInfo getAppInfo();
    ~ElectricalAssistant();

private:
    Ui::ElectricalAssistant *ui;
    appInfo appinfo;
};

#endif // ELECTRICALASSISTANT_H
