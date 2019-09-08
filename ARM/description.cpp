#include "description.h"
#include "ui_description.h"

Description::Description(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Description)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("芯片外设电路"));
}

Description::~Description()
{
    delete ui;
}
