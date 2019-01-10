#ifndef SETTINGWRAPPER_H
#define SETTINGWRAPPER_H

#include <QFrame>
#include "config.h"
#include "settingGeneral.h"
#include "settingLanguge.h"

namespace Ui {
class SettingsWrapper;
}

class SettingWrapper : public QFrame
{
    Q_OBJECT

public:
    explicit SettingWrapper(Config *config,QWidget *parent = 0);
    ~SettingWrapper();

private:
    Ui::SettingsWrapper *ui;
    Config *cfg;
    SettingsGeneral *settingsGeneral;
    SettingLanguge *settinglanguges;

};

#endif // SETTINGWRAPPER_H
