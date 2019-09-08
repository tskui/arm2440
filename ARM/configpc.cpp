#include "configpc.h"
#include "ui_configpc.h"

Configpc::Configpc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configpc)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("地址配置"));

}
int Configpc::getpcnumber(){
    return ui->pcnumber->value();
}
void Configpc::setpcnumber(int n){
    ui->pcnumber->setValue(n);
}
Configpc::~Configpc()
{
    delete ui;
}
