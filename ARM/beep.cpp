#include "beep.h"
#include "s3c2410.h"
#include <QPainter>

BEEP::BEEP(QWidget *parent) :
    QWidget(parent)
{
    t->start();
}
void BEEP::paintEvent(QPaintEvent *)
{
    quint32 GPBCON=0;
    QPainter p(this);
    QBrush b1(QColor(250,10,10));
    b1.setStyle(Qt::SolidPattern);
    QBrush b2(QColor(10,10,10));
    b2.setStyle(Qt::SolidPattern);

    p.setBrush(b2);
    p.drawEllipse(0,0,40,40);
    p.setBrush(b1);
    p.drawEllipse(15,15,10,10);
    if(ennable){
    memcontrol((quint32)rGPBDAT,true,GPBCON,4);
    if(GPBCON&0B10000)
    {
       t->startBeep();
    }else{
       t->stopBeep();
    }
    }else{
       t->stopBeep();
    }
}


