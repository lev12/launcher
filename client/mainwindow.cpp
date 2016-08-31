#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);
    ver = new versions (ui->comboBox);
    ver->FillingComboBox(ui->comboBox);

    cfg  = new config();

    QDesktopWidget *d = QApplication::desktop();
    int widthScrean = d->width();     // returns desktop width
    int heightScrean =  d->height();    // returns desktop height

    qDebug () << widthScrean;
    qDebug () << heightScrean;

    //backgroundImage = new background (this, ":/icon/background.png");

    this->setGeometry(100,100,cfg->get("width").toInt(),cfg->get("height").toInt());

    QString fullScreanStr = cfg->get("fullScrean");
    if (fullScreanStr == "false")
    {
        this->showNormal();
    }
    else if (fullScreanStr == "true")
    {
        this->showMaximized();
    }
}

MainWindow::~MainWindow()
{
    delete ver;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ver->open();
}

void MainWindow::on_folderButton_clicked()
{
    QFileInfo openFile (".//data");
    QString openPath ("file:///");
    openPath.append(openFile.absoluteFilePath());
    QDesktopServices::openUrl(QUrl(openPath, QUrl::TolerantMode));
}

void MainWindow::on_refreshButton_clicked()
{

}

void MainWindow::on_settingsButton_clicked()
{
    if (!showSettings)
    {
        setting = new settings (ui->settingsLayout->widget(),cfg);
        connect(setting,SIGNAL(close()),
                this,SLOT(on_settingsButton_clicked()));
        ui->settingsLayout->insertWidget(1,setting);
        showSettings = true;
    }
    else
    {
        ui->settingsLayout->removeWidget(setting);

        QString fullScreanStr = cfg->get("fullScrean");
        if (fullScreanStr == "false")
        {
            this->showNormal();
        }
        else if (fullScreanStr == "true")
        {
            this->showMaximized();
        }

        delete setting;
        showSettings = false;
    }
}
