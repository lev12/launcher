#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globalVariable.h"
#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QDialog>

#include "log.h"
#include "config.h"
#include "network/network.h"
#include "ui/menu.h"
#include "ui/general.h"
#include "ui/dialogupdatelauncher.h"
#include "ui/menuGeneral.h"
#include "applicationcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void connectServerStat();
    void disconnectServerStat();
    void setWidgetApp ();
    void setFullScreanMode ();
    void setNormalMode ();
    void currentLauncherVer(float ver);

private:
    Ui::MainWindow *ui;
    Config *cfg;
    Log *log;
    Network *network;
    QThread *threadNet;
    Menu *menu;
    General *general;
    DialogUpdateLauncher *updatelauncher;
    MenuGeneral *menugeneral;
    ApplicationController *appCon;
    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;
};

#endif // MAINWINDOW_H
