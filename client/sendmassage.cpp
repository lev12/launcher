#include "sendmassage.h"
#include "ui_sendmassage.h"

SendMassage::SendMassage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SendMassage)
{
    ui->setupUi(this);
}

SendMassage::~SendMassage()
{
    delete ui;
}

void SendMassage::on_pushButton_close_clicked()
{
    close();
}
