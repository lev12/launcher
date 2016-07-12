#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    client->connectToHost("192.168.0.1",80);
    versions ver(ui->comboBox);
    ver.deleteVersion("alpha", "2");
    ver.FillingComboBox(ui->comboBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    versions ver(ui->comboBox);
    ver.open();
}
