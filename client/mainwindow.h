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

#include "log.h"
#include "config.h"
#include "network.h"
#include "menu.h"
#include "electricalsimulator.h"
#include "general.h"

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
    void netError(QAbstractSocket::SocketError);

private:
    Ui::MainWindow *ui;
    config *cfg;
    Log *log;
    Network *network;
    QThread *threadNet;
    Menu *menu;
    ElectricalSimulator *electricalsimulator;
    General *general;

    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;
};

#endif // MAINWINDOW_H
