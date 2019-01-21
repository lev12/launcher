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
    explicit SettingWrapper(LauncherConfig *config,QWidget *parent = 0);
    ~SettingWrapper();

private:
    Ui::SettingsWrapper *ui;
    Config *cfg;
    SettingsGeneral *settingsGeneral;
    SettingLanguge *settinglanguges;

    QFrame *activeWidget;
public slots:
    void showGeneralSettings();
    void showLauncherSetting();

};

#endif // SETTINGWRAPPER_H
