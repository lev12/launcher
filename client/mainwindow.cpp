#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);
    ver = new versions (ui->comboBox);
    ver->FillingComboBox(ui->comboBox);

    QDesktopWidget *d = QApplication::desktop();
    int widthScrean = d->width();     // returns desktop width
    int heightScrean =  d->height();    // returns desktop height

    brush = new QBrush;
    palette = new QPalette;
    brush->setTextureImage(QImage(".//background.jpg").scaled(QSize(widthScrean,heightScrean),
                                                              Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);
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
