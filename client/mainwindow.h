#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
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
    void setWidgetApp ();
    void setFullScreanMode ();
    void setNormalMode ();

private:
    Ui::MainWindow *ui;
    Network *network;
    Menu *menu;
    config *cfg;
    ElectricalSimulator *electricalsimulator;
    General *general;

    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;
};

#endif // MAINWINDOW_H
