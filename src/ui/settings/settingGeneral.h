#ifndef SETTINGSGENERAL_H
#define SETTINGSGENERAL_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLine>
#include "launcherConfig.h"
#include "settingCheckBox.h"
#include "settingSpinBox.h"

class SettingsGeneral : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsGeneral(QWidget *parent = nullptr);
    ~SettingsGeneral();

private:
    LauncherConfig *cfg;

    QVBoxLayout *content;
    SettingSpinBox *uiWidth;
    SettingSpinBox *uiHeight;
    settingCheckbox *uiFullScrean;
    SettingSpinBox *uiScale;
    bool *fullscrean;
    QLocale::Language *language;
    bool *logState;
    int *interfaceSize;
    bool *checkUpdateLauncher;

signals:
    void showSettingsLanguges();
};

#endif // SETTINGSGENERAL_H
