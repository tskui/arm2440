#include "lcd.h"
#include "ui_lcd.h"
#include <QPainter>
extern quint8 Member[1024*4];
LCD::LCD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LCD)
{
    ui->setupUi(this);
}
void LCD::paintEvent(QPaintEvent *){
    QPainter p(this);

    QBrush b1(QColor(172,172,172));
    b1.setStyle(Qt::SolidPattern);
    p.setBrush(b1);
    p.drawRect(0,0,this->geometry().width(),this->geometry().height());

    QBrush b2(QColor(133,197,83));
    b2.setStyle(Qt::SolidPattern);
    p.setBrush(b2);
    p.drawRect(10,10,this->width()-20,this->height()-20);
    if(this->ennable){
       QBrush b3(QColor(0,0,0));
       p.setBrush(b3);
       QFont f=p.font();
       f.setPointSize(26);
       p.setFont(f);
       for(int i=0;i<9;i++){
           for(int j=0;j<9;j++){
               str[i][j]=Member[4000+i*9+j];
           }
       }
       p.drawText(QPoint(20,40),str[0]);
       p.drawText(QPoint(20,70),str[1]);
       p.drawText(QPoint(20,100),str[2]);
       p.drawText(QPoint(20,130),str[3]);
       p.drawText(QPoint(20,160),str[4]);
       p.drawText(QPoint(20,190),str[5]);
       p.drawText(QPoint(20,220),str[6]);
       p.drawText(QPoint(20,250),str[7]);
       p.drawText(QPoint(20,280),str[8]);
      
    }else{
        p.drawRect(10,10,this->width()-20,this->height()-20);
    }


}
LCD::~LCD()
{
    delete ui;
}
