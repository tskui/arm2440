#include "lcdnumber.h"
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <s3c2410.h>
LCDNUMBER::LCDNUMBER(QWidget *parent) :
    QWidget(parent)
{
    this->numdate=0;
}
void LCDNUMBER::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QBrush b(QColor(0,0,0));
    b.setStyle(Qt::SolidPattern);
    p.setBrush(b);
    p.drawRect(0,0,this->geometry().width(),this->geometry().height());
    QBrush b1(QColor(250,10,10));
    b1.setStyle(Qt::SolidPattern);

    QBrush b2(QColor(250,250,250));
    b2.setStyle(Qt::SolidPattern);
    memcontrol((quint32)rGPBDAT,true,this->numdate,4);
    quint32 FLAG=0;
    if(ennable){
    memcontrol(rGPFDAT,true,FLAG,4);
    if(FLAG&0B00010000){
        if(numdate&0X01000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(3,0,27,6);
        if(numdate&0X02000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(0,3,6,27);
        if(numdate&0X04000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(27,3,6,27);
        if(numdate&0X08000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(3,27,27,6);
        if(numdate&0X10000000){
            p.setBrush(b1);

        }
        else{
            p.setBrush(b2);

        }
        p.drawRect(0,30,6,27);
        if(numdate&0X20000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(27,30,6,27);
        if(numdate&0X40000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(3,54,27,6);
        if(numdate&0X80000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(40,54,6,6);

    }else{
        p.setBrush(b2);
        p.drawRect(3,0,27,6);
        p.drawRect(0,3,6,27);
        p.drawRect(27,3,6,27);
        p.drawRect(3,27,27,6);
        p.drawRect(0,30,6,27);
        p.drawRect(27,30,6,27);
        p.drawRect(3,54,27,6);
        p.drawRect(40,54,6,6);

    }
    if(FLAG&0B00100000){
        if(numdate&0X010000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+3,0,27,6);
        if(numdate&0X020000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+0,3,6,27);
        if(numdate&0X040000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+27,3,6,27);
        if(numdate&0X080000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+3,27,27,6);
        if(numdate&0X100000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+0,30,6,27);
        if(numdate&0X200000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+27,30,6,27);
        if(numdate&0X400000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+3,54,27,6);
        if(numdate&0X800000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(50+40,54,6,6);
    }else{
        p.setBrush(b2);
        p.drawRect(50+3,0,27,6);
        p.drawRect(50+0,3,6,27);
        p.drawRect(50+27,3,6,27);
        p.drawRect(50+3,27,27,6);
        p.drawRect(50+0,30,6,27);
        p.drawRect(50+27,30,6,27);
        p.drawRect(50+3,54,27,6);
        p.drawRect(50+40,54,6,6);
    }
    if(FLAG&0B01000000){
        if(numdate&0X0100){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+3,0,27,6);
        if(numdate&0X0200){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+0,3,6,27);
        if(numdate&0X0400){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+27,3,6,27);
        if(numdate&0X0800){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+3,27,27,6);
        if(numdate&0X1000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+0,30,6,27);
        if(numdate&0X2000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+27,30,6,27);
        if(numdate&0X4000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+3,54,27,6);
        if(numdate&0X8000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(100+40,54,6,6);

    }else{
        p.setBrush(b2);
        p.drawRect(100+3,0,27,6);
        p.drawRect(100+0,3,6,27);
        p.drawRect(100+27,3,6,27);
        p.drawRect(100+3,27,27,6);
        p.drawRect(100+0,30,6,27);
        p.drawRect(100+27,30,6,27);
        p.drawRect(100+3,54,27,6);
        p.drawRect(100+40,54,6,6);
    }
    if(FLAG&0B10000000){
        if(numdate&0B1){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+3,0,27,6);
        if(numdate&0B10){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+0,3,6,27);
        if(numdate&0B100){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+27,3,6,27);
        if(numdate&0B1000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+3,27,27,6);
        if(numdate&0B10000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+0,30,6,27);
        if(numdate&0B100000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+27,30,6,27);
        if(numdate&0B1000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+3,54,27,6);
        if(numdate&0B10000000){
            p.setBrush(b1);
        }
        else{
            p.setBrush(b2);
        }
        p.drawRect(150+40,54,6,6);

    }else{
        p.setBrush(b2);
        p.drawRect(150+3,0,27,6);
        p.drawRect(150+0,3,6,27);
        p.drawRect(150+27,3,6,27);
        p.drawRect(150+3,27,27,6);
        p.drawRect(150+0,30,6,27);
        p.drawRect(150+27,30,6,27);
        p.drawRect(150+3,54,27,6);
        p.drawRect(150+40,54,6,6);
    }
    }else{
        p.setBrush(b2);
        p.drawRect(3,0,27,6);
        p.drawRect(0,3,6,27);
        p.drawRect(27,3,6,27);
        p.drawRect(3,27,27,6);
        p.drawRect(0,30,6,27);
        p.drawRect(27,30,6,27);
        p.drawRect(3,54,27,6);
        p.drawRect(40,54,6,6);

        p.drawRect(50+3,0,27,6);
        p.drawRect(50+0,3,6,27);
        p.drawRect(50+27,3,6,27);
        p.drawRect(50+3,27,27,6);
        p.drawRect(50+0,30,6,27);
        p.drawRect(50+27,30,6,27);
        p.drawRect(50+3,54,27,6);
        p.drawRect(50+40,54,6,6);

        p.drawRect(100+3,0,27,6);
        p.drawRect(100+0,3,6,27);
        p.drawRect(100+27,3,6,27);
        p.drawRect(100+3,27,27,6);
        p.drawRect(100+0,30,6,27);
        p.drawRect(100+27,30,6,27);
        p.drawRect(100+3,54,27,6);
        p.drawRect(100+40,54,6,6);

        p.drawRect(150+3,0,27,6);
        p.drawRect(150+0,3,6,27);
        p.drawRect(150+27,3,6,27);
        p.drawRect(150+3,27,27,6);
        p.drawRect(150+0,30,6,27);
        p.drawRect(150+27,30,6,27);
        p.drawRect(150+3,54,27,6);
        p.drawRect(150+40,54,6,6);
    }

}
void LCDNUMBER::clear()
{
    this->numdate=0;
    this->updateGeometry();

}
