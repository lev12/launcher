#ifndef SETTINGLANGUGES_H
#define SETTINGLANGUGES_H

#include <QFrame>
#include <QLocale>
#include "settingGeneral.h"

namespace Ui {
class SettingLanguges;
}

class SettingLanguge : public QFrame
{
    Q_OBJECT

public:
    explicit SettingLanguge(SettingsGeneral *settingsGeneral,QWidget *parent = 0);
    ~SettingLanguge();

private:
    Ui::SettingLanguges *ui;
    QLocale::Language *language;

signals:
    void back();
};

#endif // SETTINGLANGUGES_H
