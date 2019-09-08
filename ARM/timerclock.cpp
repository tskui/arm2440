#include "timerclock.h"
#include "s3c2410.h"
#include <QDebug>
quint16 timerclock::TCMPB0=0;
quint16 timerclock::TCMPB1=0;
quint16 timerclock::TCMPB2=0;
quint16 timerclock::TCMPB3=0;
quint16 timerclock::TCNTB0=0;
quint16 timerclock::TCNTB1=0;
quint16 timerclock::TCNTB2=0;
quint16 timerclock::TCNTB3=0;
quint16 timerclock::TCNTB4=0;
bool timerclock::startflag0=false;
bool timerclock::startflag1=false;
bool timerclock::startflag2=false;
bool timerclock::startflag3=false;
bool timerclock::startflag4=false;
extern  bool isjump;
timerclock::timerclock(){  }
void timerclock::timer(){
    //定时器 位[19:12]为MDIV，位[9:4]为PDIV，位[1:0]为SDIV，FCLK与Fin的关系如下
    //FCLK=（2*m*Fin）/（p*2^s） m=MDIV+8， p=PDIV+2， s=SDIV
    int Fin;
    static quint8 n=0;
    quint32 buffer=0,MDIV,PDIV,SDIV,FCLK,HCLK,PCLK;
    memcontrol((quint32)rMPLLCON,true,buffer,4);
    MDIV=(buffer>>12)&255;
    PDIV=(buffer>>4)&0B111111;
    SDIV=(buffer)&0B11;
    FCLK=(2*(MDIV+8)*Fin)/((PDIV+2)*2^(SDIV));
    memcontrol((quint32)rCLKDIVN,true,buffer,4);
    switch (buffer&0b111) {
    case 0:HCLK=FCLK;PCLK=FCLK;
        break;
    case 1:HCLK=FCLK;PCLK=FCLK+FCLK;
        break;
    case 2:HCLK=FCLK+FCLK;PCLK=FCLK+FCLK;
        break;
    case 3:HCLK=FCLK+FCLK;PCLK=FCLK+FCLK+FCLK+FCLK;
        break;
    case 4:HCLK=FCLK+FCLK+FCLK+FCLK;PCLK=FCLK+FCLK+FCLK+FCLK;
        break;
    case 5:HCLK=FCLK+FCLK+FCLK+FCLK;PCLK=FCLK+FCLK+FCLK+FCLK+FCLK+FCLK+FCLK+FCLK;
        break;
    case 6:HCLK=FCLK+FCLK+FCLK;PCLK=FCLK+FCLK+FCLK;
        break;
    case 7:HCLK=FCLK+FCLK+FCLK;PCLK=FCLK+FCLK+FCLK+FCLK+FCLK+FCLK;
        break;
    default:
        break;
    }
    quint32  prescaler0,prescaler1,dv0,dv1,dv2,dv3,dv4;
    memcontrol((quint32)rTCFG0,true,buffer,4);
    prescaler0=buffer&255;prescaler1=(buffer>>8)&255;
    memcontrol((quint32)rTCFG1,true,buffer,4);
    dv0=2^((buffer&15)+1);
    dv1=2^(((buffer>>4)&15)+1);
    dv2=2^(((buffer>>8)&15)+1);
    dv3=2^(((buffer>>12)&15)+1);
    dv4=2^(((buffer>>16)&15)+1);

    dv0=(PCLK/(prescaler0+1)/dv0);
    dv1=(PCLK/(prescaler0+1)/dv1);

    dv2=(PCLK/(prescaler1+1)/dv2);
    dv3=(PCLK/(prescaler1+1)/dv3);
    dv4=(PCLK/(prescaler1+1)/dv4);

    memcontrol((quint32)rTCON,true,buffer,4);


}
//SRCPND寄存器中的相应位置1，仲裁过程结束后INTPND寄存器中只有1位
void timerclock::exectimer(){
     quint32 TCON=0,flag,flag2=0;
     memcontrol((quint32)rTCON,true,TCON,4);
     if(TCON&1){//定时器0开启
        if(TCNTB0==0){
            //isjump=true;
            flag=1;
            flag2=flag2|(flag<<11);
            }
        TCNTB0--;
        flag=TCNTB0;
        memcontrol((quint32)rTCNTO0,false,flag,4);
        qDebug()<<QString("TCNTB0=%1").arg(TCNTB0);

     }else{
        TCNTB0=0;
     }
     if(TCON&0B100000000){//定时器1开启
        if(TCNTB1==0){
            //isjump=true;
            flag=1;
            flag2=flag2|(flag<<12);
            }
        TCNTB1--;
        flag=TCNTB1;
        memcontrol((quint32)rTCNTO1,false,flag,4);
        qDebug()<<QString("TCNTB1=%1").arg(TCNTB1);
     }else{
        TCNTB1=0;
     }
     if(TCON&0B1000000000000){//定时器2开启
        if(TCNTB2==0){
            //isjump=true;
            flag=1;
            flag2=flag2|(flag<<13);
            }
        TCNTB2--;
        flag=TCNTB2;
        memcontrol((quint32)rTCNTO2,false,flag,4);
        qDebug()<<QString("TCNTB2=%1").arg(TCNTB2);
     }else{
        TCNTB2=0;
     }
     if(TCON&0B10000000000000000){//定时器3开启
        if(TCNTB3==0){
            //isjump=true;
            flag=1;
            flag2=flag2|(flag<<14);
           }
        TCNTB3--;
        flag=TCNTB3;
        memcontrol((quint32)rTCNTO3,false,flag,4);
        qDebug()<<QString("TCNTB3=%1").arg(TCNTB3);
     }else{
        TCNTB3=0;
     }
     if(TCON&0B100000000000000000000){//定时器4开启 无输出
        if(TCNTB4==0){
            //isjump=true;
            flag=1;
            flag2=flag2|(flag<<15);
            }
        TCNTB4--;
        flag=TCNTB4;
        memcontrol((quint32)rTCNTO4,false,flag,4);
        qDebug()<<QString("TCNTB4=%1").arg(TCNTB4);
     }else{
         TCNTB4=0;
     }
     if(flag2!=0)memcontrol((quint32)rSRCPND,false,flag2,4);
}
