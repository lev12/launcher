#ifndef SETTINGSGENERAL_H
#define SETTINGSGENERAL_H

#include <QFrame>
#include "config.h"

namespace Ui {
class SettingsGeneral;
}

class SettingsGeneral : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsGeneral(Config *config,QWidget *parent = 0);
    ~SettingsGeneral();

private:
    Ui::SettingsGeneral *ui;
    Config *cfg;
    bool *fullscrean;
    QLocale::Language *language;
    bool *logState;
    int *interfaceSize;
    bool *checkUpdateLauncher;

signals:
    void showSettingsLanguges();
};

#endif // SETTINGSGENERAL_H
