#include <QCoreApplication>
#include "C_SPSR.h"
#include <QDebug>
extern quint32 R[16];
void msr(quint32 IR){
    switch ((IR>>28)&15) {
    case 0:if(1==((CPSR>>30)&1)){goto condition;}break;//相等z
    case 1:if(0==((CPSR>>30)&1)){goto condition;}break;//不等
    case 2:if(1==((CPSR>>29)&1)){goto condition;}break;//>=c
    case 3:if(0==((CPSR>>29)&1)){goto condition;}break;//<
    case 4:if(1==((CPSR>>31)&1)){goto condition;}break;//n
    case 5:if(0==((CPSR>>31)&1)){goto condition;}break;
    case 6:if(1==((CPSR>>28)&1)){goto condition;}break;//v
    case 7:if(0==((CPSR>>28)&1)){goto condition;}break;
    case 8:if((1==((CPSR>>29)&1))&&(0==((CPSR>>30)&1))){goto condition;}break;
    case 9:if((0==((CPSR>>29)&1))&&(1==((CPSR>>30)&1))){goto condition;}break;
    case 10:if(((CPSR>>31)&1)==((CPSR>>28)&1)){goto condition;}break;
    case 11:if(((CPSR>>31)&1)!=((CPSR>>28)&1)){goto condition;}break;
    case 12:if((0==((CPSR>>30)&1))&&(((CPSR>>31)&1)==((CPSR>>28)&1))){goto condition;}break;
    case 13:if((1==((CPSR>>30)&1))||(((CPSR>>31)&1)!=((CPSR>>28)&1))){goto condition;}break;
    case 14:goto condition;break;
    default:
        break;
    }
    return;
condition:
    quint32 Rm=IR&15;
    if((IR>>22)&1){
        switch (CPSR&0b11111) {
        case 0b10000://user model
            CPSR=R[Rm];
            break;
        case 0b10001://fiq model
            SPSR_FIQ=R[Rm];
            break;
        case 0b10010://irq model
            SPSR_IRQ=R[Rm];
            break;
        case 0b10011://super model
            SPSR_SUPERVISOR=R[Rm];
            break;
        case 0b10111://Abort model
            SPSR_ABORT=R[Rm];
            break;
        case 0b11011://undefine model
            SPSR_UNDEFINEED=R[Rm];
            break;
        case 0b11111://system model
            CPSR=R[Rm];
            break;
        default:
            break;
        }

    }else{
      CPSR=R[Rm];
    }
}
void msr_im(quint32 IR){
    switch ((IR>>28)&15) {
    case 0:if(1==((CPSR>>30)&1)){goto condition;}break;//相等z
    case 1:if(0==((CPSR>>30)&1)){goto condition;}break;//不等
    case 2:if(1==((CPSR>>29)&1)){goto condition;}break;//>=c
    case 3:if(0==((CPSR>>29)&1)){goto condition;}break;//<
    case 4:if(1==((CPSR>>31)&1)){goto condition;}break;//n
    case 5:if(0==((CPSR>>31)&1)){goto condition;}break;
    case 6:if(1==((CPSR>>28)&1)){goto condition;}break;//v
    case 7:if(0==((CPSR>>28)&1)){goto condition;}break;
    case 8:if((1==((CPSR>>29)&1))&&(0==((CPSR>>30)&1))){goto condition;}break;
    case 9:if((0==((CPSR>>29)&1))&&(1==((CPSR>>30)&1))){goto condition;}break;
    case 10:if(((CPSR>>31)&1)==((CPSR>>28)&1)){goto condition;}break;
    case 11:if(((CPSR>>31)&1)!=((CPSR>>28)&1)){goto condition;}break;
    case 12:if((0==((CPSR>>30)&1))&&(((CPSR>>31)&1)==((CPSR>>28)&1))){goto condition;}break;
    case 13:if((1==((CPSR>>30)&1))||(((CPSR>>31)&1)!=((CPSR>>28)&1))){goto condition;}break;
    case 14:goto condition;break;
    default:
        break;
    }
    return;
condition:
    quint32 im=IR&0b11111111,rotate=(IR>>8)&15;
    im=im<<(32-rotate-rotate);
    im=im|((IR&255)>>(rotate+rotate));
    if((IR>>22)&1){
        switch (CPSR&0b11111) {
        case 0b10000://user model
            CPSR=im;
            break;
        case 0b10001://fiq model
            SPSR_FIQ=im;
            break;
        case 0b10010://irq model
            SPSR_IRQ=im;
            break;
        case 0b10011://super model
            SPSR_SUPERVISOR=im;
            break;
        case 0b10111://Abort model
            SPSR_ABORT=im;
            break;
        case 0b11011://undefine model
            SPSR_UNDEFINEED=im;
            break;
        case 0b11111://system model
            CPSR=im;
            break;
        default:
            break;
        }

    }else{
           CPSR=im;
    }
}
void mrs(quint32 IR){
    switch ((IR>>28)&15) {
    case 0:if(1==((CPSR>>30)&1)){goto condition;}break;//相等z
    case 1:if(0==((CPSR>>30)&1)){goto condition;}break;//不等
    case 2:if(1==((CPSR>>29)&1)){goto condition;}break;//>=c
    case 3:if(0==((CPSR>>29)&1)){goto condition;}break;//<
    case 4:if(1==((CPSR>>31)&1)){goto condition;}break;//n
    case 5:if(0==((CPSR>>31)&1)){goto condition;}break;
    case 6:if(1==((CPSR>>28)&1)){goto condition;}break;//v
    case 7:if(0==((CPSR>>28)&1)){goto condition;}break;
    case 8:if((1==((CPSR>>29)&1))&&(0==((CPSR>>30)&1))){goto condition;}break;
    case 9:if((0==((CPSR>>29)&1))&&(1==((CPSR>>30)&1))){goto condition;}break;
    case 10:if(((CPSR>>31)&1)==((CPSR>>28)&1)){goto condition;}break;
    case 11:if(((CPSR>>31)&1)!=((CPSR>>28)&1)){goto condition;}break;
    case 12:if((0==((CPSR>>30)&1))&&(((CPSR>>31)&1)==((CPSR>>28)&1))){goto condition;}break;
    case 13:if((1==((CPSR>>30)&1))||(((CPSR>>31)&1)!=((CPSR>>28)&1))){goto condition;}break;
    case 14:goto condition;break;
    default:
        break;
    }
    return;
condition:
    quint32 Rd=(IR>>12)&15;
    if((IR>>22)&1){
        //qDebug()<<"mrs duo";
        switch (CPSR&0b11111) {
        case 0b10000://user model
            R[Rd]=CPSR;
            break;
        case 0b10001://fiq model
            R[Rd]=SPSR_FIQ;
            break;
        case 0b10010://irq model
            R[Rd]=SPSR_IRQ;
            break;
        case 0b10011://super model
            R[Rd]=SPSR_SUPERVISOR;
            break;
        case 0b10111://Abort model
            R[Rd]=SPSR_ABORT;
            break;
        case 0b11011://undefine model
            R[Rd]=SPSR_UNDEFINEED;
            break;
        case 0b11111://system model
            R[Rd]=CPSR;
            break;
        default:
            break;
        }
    }else{//cpsr
       //qDebug()<<"mrs cpsr";
       R[Rd]=CPSR;
    }
}
