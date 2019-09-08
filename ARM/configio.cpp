#include "configio.h"
#include "ui_configio.h"
#include <QDebug>
Configio::Configio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configio)
{
    ui->setupUi(this);
    this->setWindowTitle("端口配置");
}

Configio::~Configio()
{
    delete ui;
}
void Configio::cfgbeep(BEEP *beep){
    if(ui->radioButton_5->isChecked()){
        beep->ennable=true;
    }else{
        beep->ennable=false;
    }
}
void Configio::cfgled(lamb *lamb){
    if(ui->radioButton->isChecked()){
        lamb->ennable=true;
    }else{
        lamb->ennable=false;
    }
}
void Configio::cfgLCDNUMBER(LCDNUMBER *lcdnumber){
    if(ui->radioButton_3->isChecked()){
        lcdnumber->ennable=true;
    }else{
        lcdnumber->ennable=false;
    }
}
void Configio::cfgLCD(LCD *lcd){
    if(ui->radioButton_7->isChecked()){
        lcd->ennable=true;
        //qDebug()<<"lcd-------------true";
    }else{
        lcd->ennable=false;
        //qDebug()<<"lcd-------------false";
    }
}
void Configio::checkstate(BEEP *beep,lamb *lamb,LCDNUMBER *lcdnumber,LCD *lcd){
    if(beep->ennable){
        ui->radioButton_5->setChecked(true);
    }else{
        ui->radioButton_6->setChecked(true);
    }
    if(lamb->ennable){
        ui->radioButton->setChecked(true);
    }else{
        ui->radioButton_2->setChecked(true);
    }
    if(lcdnumber->ennable){
        ui->radioButton_3->setChecked(true);
    }else{
        ui->radioButton_4->setChecked(true);
    }
    if(lcd->ennable){
        ui->radioButton_7->setChecked(true);
    }else{
        ui->radioButton_8->setChecked(true);
    }
}
