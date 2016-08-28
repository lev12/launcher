#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

}

settings::~settings()
{
    delete ui;
}

void settings::on_pushButton_clicked()
{
    if (!fullScrean)
    {
        ui->pushButton->setIcon(QIcon(":/icon/checkBox on.png"));
        fullScrean = true;
    }else
    {
        ui->pushButton->setIcon(QIcon (":/icon/off.png"));
        fullScrean = false;
    }
}
