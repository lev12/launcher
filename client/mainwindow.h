#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QWidget>
#include "network.h"
#include "menu.h"
#include "electricalsimulator.h"

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
    void setWidgetApp ();

private:
    Ui::MainWindow *ui;
    //versions *ver;
    Network *network;
    Menu *menu;
    config *cfg;
    background *backgroundImage;
    ElectricalSimulator *app;

    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;
};

#endif // MAINWINDOW_H
