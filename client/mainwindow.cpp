#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setCentralWidget(ui->verticalFrame);
    ver = new versions (ui->comboBox);
    ver->FillingComboBox(ui->comboBox);

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
