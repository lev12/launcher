#ifndef SETTINGLANGUGES_H
#define SETTINGLANGUGES_H

#include <QFrame>
#include <QLocale>
#include "settingsGeneral.h"

namespace Ui {
class SettingLanguges;
}

class SettingLanguges : public QFrame
{
    Q_OBJECT

public:
    explicit SettingLanguges(SettingsGeneral *settingsGeneral,QWidget *parent = 0);
    ~SettingLanguges();

private:
    Ui::SettingLanguges *ui;
    QLocale::Language *language;

signals:
    void back();
};

#endif // SETTINGLANGUGES_H
