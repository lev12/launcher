#include "general.h"
#include "ui_general.h"

General::General(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::General)
{
    ui->setupUi(this);
}

General::~General()
{
    delete ui;
}