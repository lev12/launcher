#ifndef SETTINGWRAPPER_H
#define SETTINGWRAPPER_H

#include <QFrame>
#include "config.h"
#include "settingGeneral.h"
#include "settingLanguge.h"
#include "ui/abstractWindow.h"

/*!
 * Id 11
 */
namespace Ui {
class SettingsWrapper;
}

class SettingWrapper : public AbstractWindow
{
    Q_OBJECT

public:
    explicit SettingWrapper(LauncherConfig *config,QWidget *parent = nullptr);
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
