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
#include <QDebug>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>

#include "log.h"
#include "config.h"
#include "network/network.h"
#include "ui/uiHomePage.h"
#include "ui/uiMainMenu.h"
#include "ui/uiApplication.h"
#include "ui/uiApplicationInstalled.h"

#include "ui/dialogUpdateLauncher.h"
#include "applicationController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setUiApplication(UiApplication *app);
    void setHomePage();
    void setApplicationInstalled();

private slots:
    void setWidgetApp ();
    void setFullScreanMode ();
    void setNormalMode ();
    void currentLauncherVer(float ver);

private:
    Ui::MainWindow *ui;
    Log *log;
    Network *network;
    DialogUpdateLauncher *updatelauncher;
    ApplicationController *appCon;
    UiMainMenu *mainMenu;
    UiHomePage *homePage;
    UiApplicationInstalled *appInstallPage;

    QFrame *activeFrame;
    void removeActiveFrame();
    void setActiveFrame(QFrame *f);
};

#endif // MAINWINDOW_H
