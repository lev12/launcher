#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    versions ver(ui->comboBox);
    ver.FillingComboBox(ui->comboBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    //ver.open();
}
