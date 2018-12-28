#ifndef SETTINGWRAPPER_H
#define SETTINGWRAPPER_H

#include <QFrame>
#include "config.h"
#include "settingsGeneral.h"
#include "settingLanguges.h"

namespace Ui {
class SettingsWrapper;
}

class SettingsWrapper : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsWrapper(Config *config,QWidget *parent = 0);
    ~SettingsWrapper();

private:
    Ui::SettingsWrapper *ui;
    Config *cfg;
    SettingsGeneral *settingsGeneral;
    SettingLanguges *settinglanguges;

};

#endif // SETTINGWRAPPER_H
