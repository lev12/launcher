#ifndef ELECTRICALSIMULATOR_H
#define ELECTRICALSIMULATOR_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
//#include "global_variable.h"
#include "settings.h"
#include "background.h"
#include "application.h"

namespace Ui {
class ElectricalSimulator;
}

class ElectricalSimulator : public QFrame
{
    Q_OBJECT
private slots:
    void on_pushButton_clicked();
    void on_folderButton_clicked();
    void on_refreshButton_clicked();
    void on_settingsButton_clicked();

public:

    explicit ElectricalSimulator(QWidget *parent = 0);
    ~ElectricalSimulator();

    virtual appInfo getAppInfo ();

    config *cfg;
    bool showSettings = false;
    settings *setting;
    Ui::ElectricalSimulator *ui;
private:
    appInfo appinfo;

};

#endif // ELECTRICALSIMULATOR_H
