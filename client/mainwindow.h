#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global_variable.h"
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
#include "network.h"
#include "menu.h"
#include "electricalassistant.h"
#include "electricalsimulator.h"
#include "general.h"
#include "dialogupdatelauncher.h"

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
    void netError(QAbstractSocket::SocketError);

private:
    Ui::MainWindow *ui;
    config *cfg;
    Log *log;
    Network *network;
    QThread *threadNet;
    Menu *menu;
    ElectricalAssistant *electricalassistant;
    ElectricalSimulator *electricalsimulator;
    General *general;
    DialogUpdateLauncher *updatelauncher;

    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;
};

#endif // MAINWINDOW_H
