#include "member.h"
#include "ui_member.h"
extern void memcontrol(quint32 addr,bool isread,quint32 & taget,quint8 size=4);
Member::Member(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);
    this->setWindowTitle("内存视图");
    this->on_pushButton_clicked();

}

Member::~Member()
{
    delete ui;
}

void Member::on_pushButton_clicked()
{
   int value=ui->spinBox->value();
   ui->textEdit->clear();
   quint32 c=0;
   QString text;
   quint32 n;
   for(int i=0;i<512;i+=4){
       memcontrol(value+i,true,c,4);
       if(c==0){
           text+=QString("00 00 00 00 ");
       }else{
           n=c&255;
           if(n<16){
               text+=("0"+QString::number(n,16).toUpper()+" ");
           }else{
               text+=(""+QString::number(n,16).toUpper()+" ");
           }
           n=(c>>8)&255;
           if(n<16){
               text+=("0"+QString::number(n,16).toUpper()+" ");
           }else{
               text+=(""+QString::number(n,16).toUpper()+" ");
           }
           n=(c>>16)&255;
           if(n<16){
               text+=("0"+QString::number(n,16).toUpper()+" ");
           }else{
               text+=(""+QString::number(n,16).toUpper()+" ");
           }
           n=(c>>24)&255;
           if(n<16){
               text+=("0"+QString::number(n,16).toUpper()+" ");
           }else{
               text+=(""+QString::number(n,16).toUpper()+" ");
           }
       }
   }
   ui->textEdit->setText(text);
}
