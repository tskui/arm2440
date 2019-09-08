#include "lamb.h"
#include <QCoreApplication>
#include <QLatin1String>
#include <QPainter>
#include <QDebug>
#include <s3c2410.h>
lamb::lamb(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet(QLatin1String("background-color: rgb(85, 2, 127)"));
}
void lamb::paintEvent(QPaintEvent *){
    quint32 GPBCON=0,GPBDAT=0;
    QPainter p(this);
    QBrush b1(QColor(250,10,10));
    b1.setStyle(Qt::SolidPattern);
    QBrush b2(QColor(10,10,10));
    b2.setStyle(Qt::SolidPattern);
    memcontrol((quint32)rGPBCON,true,GPBCON,4);
    memcontrol((quint32)rGPBDAT,true,GPBDAT,4);
    if(ennable){
    p.setBrush(b1);
    if((GPBCON&0B11)==0B01){
        if((GPBDAT&0B1)){
             p.setBrush(b1);
        }
        else{
             p.setBrush(b2);
        }
    }
    p.drawEllipse(0,0,20,20);
    p.setBrush(b1);
    if((GPBCON&0B1100)==0B0100){
        if((GPBDAT&0B10)){
             p.setBrush(b1);
        }
        else{
             p.setBrush(b2);
        }
    }
    p.drawEllipse(0,40,20,20);
    p.setBrush(b1);
    if((GPBCON&0B110000)==0B010000){
        if((GPBDAT&0B100)){
             p.setBrush(b1);
        }
        else{
             p.setBrush(b2);
        }
    }
    p.drawEllipse(0,80,20,20);
    p.setBrush(b1);
    if((GPBCON&0B11000000)==0B01000000){
        if((GPBDAT&0B1000)){
             p.setBrush(b1);
        }
        else{
             p.setBrush(b2);
        }
    }
    p.drawEllipse(0,120,20,20);
    }else{
    p.setBrush(b2);
    p.drawEllipse(0,0,20,20);
    p.drawEllipse(0,40,20,20);
    p.drawEllipse(0,80,20,20);
    p.drawEllipse(0,120,20,20);
    }
    //qDebug()<<"________"+QString::number(GPFCON,16);
}
