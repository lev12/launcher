#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QApplication>
#include "versions.h"
#include "settings.h"
#include "background.h"
#include "network.h"
#include "menu.h"

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
    void on_pushButton_clicked();
    void on_folderButton_clicked();
    void on_refreshButton_clicked();
    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    //versions *ver;
    Network *network;
    Menu *menu;
    config *cfg;
    background *backgroundImage;

    settings *setting;
    QBrush *brush;
    QPalette *palette;
    QDesktopWidget *d;

    bool showSettings = false;
};

#endif // MAINWINDOW_H
