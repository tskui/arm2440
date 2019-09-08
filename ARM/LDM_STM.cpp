#include <QCoreApplication>
#include "C_SPSR.h"
extern void memcontrol(quint32 addr,bool isread,quint32 & taget,quint8 size=4);
extern quint32 R[16];
extern quint8 Member[1024*4];
extern quint32 CYC_BUFFER;
extern quint32 CPSR;//程序状态寄存器N Z C V Q DNM(RAZ) I F T M4 M3 M2 M1 M0
extern quint32 SPSR_FIQ;//程序状态保存寄存器
extern quint32 SPSR_IRQ;//程序状态保存寄存器
extern quint32 SPSR_SUPERVISOR;//程序状态保存寄存器
extern quint32 SPSR_ABORT;//程序状态保存寄存器
extern quint32 SPSR_UNDEFINEED;//程序状态保存寄存器
void LDM_STM(quint32 IR){
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
    quint32 pos=0,Rn=((IR>>16)&15),Rlist=((IR)&0b1111111111111111);
    pos=R[Rn];
         if(1==((IR>>20)&1)){//ldm
                // p=1先减去后传 u=0减 s=0不载入psr或者user模式  w=1写回基地址
                 switch ((IR>>21)&15){
                     //pusw
                 case 0B0000:
                     //先传后减 不歇会
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos-4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos-4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos-4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos-4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos-4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos-4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos-4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos-4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos-4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos-4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos-4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos-4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos-4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos-4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos-4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos-4;}
                     break;
                 case 0B0001:
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos-4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos-4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos-4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos-4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos-4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos-4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos-4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos-4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos-4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos-4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos-4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos-4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos-4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos-4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos-4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos-4;}
                     R[Rn]=pos;
                     break;
                 case 0B0010://模式
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos-4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos-4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos-4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos-4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos-4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos-4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos-4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos-4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos-4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos-4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos-4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos-4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos-4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos-4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos-4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos-4;}
                     break;
                 case 0B0011://模式
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos-4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos-4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos-4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos-4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos-4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos-4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos-4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos-4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos-4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos-4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos-4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos-4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos-4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos-4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos-4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos-4;}
                     R[Rn]=pos;
                     break;
                 case 0B0100:
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos+4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos+4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos+4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos+4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos+4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos+4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos+4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos+4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos+4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos+4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos+4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos+4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos+4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos+4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos+4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos+4;}
                     break;
                 case 0B0101:
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos+4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos+4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos+4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos+4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos+4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos+4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos+4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos+4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos+4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos+4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos+4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos+4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos+4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos+4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos+4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos+4;}
                     R[Rn]=pos;
                     break;
                 case 0B0110://模式
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos+4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos+4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos+4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos+4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos+4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos+4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos+4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos+4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos+4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos+4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos+4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos+4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos+4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos+4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos+4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos+4;}
                     break;
                 case 0B0111:
                     if(Rlist&0b1000000000000000){memcontrol(pos,true,R[15],4);pos=pos+4;}
                     if(Rlist&0b100000000000000){memcontrol(pos,true,R[14],4);pos=pos+4;}
                     if(Rlist&0b10000000000000){memcontrol(pos,true,R[13],4);pos=pos+4;}
                     if(Rlist&0b1000000000000){memcontrol(pos,true,R[12],4);pos=pos+4;}
                     if(Rlist&0b100000000000){memcontrol(pos,true,R[11],4);pos=pos+4;}
                     if(Rlist&0b10000000000){memcontrol(pos,true,R[10],4);pos=pos+4;}
                     if(Rlist&0b1000000000){memcontrol(pos,true,R[9],4);pos=pos+4;}
                     if(Rlist&0b100000000){memcontrol(pos,true,R[8],4);pos=pos+4;}
                     if(Rlist&0b10000000){memcontrol(pos,true,R[7],4);pos=pos+4;}
                     if(Rlist&0b1000000){memcontrol(pos,true,R[6],4);pos=pos+4;}
                     if(Rlist&0b100000){memcontrol(pos,true,R[5],4);pos=pos+4;}
                     if(Rlist&0b10000){memcontrol(pos,true,R[4],4);pos=pos+4;}
                     if(Rlist&0b1000){memcontrol(pos,true,R[3],4);pos=pos+4;}
                     if(Rlist&0b100){memcontrol(pos,true,R[2],4);pos=pos+4;}
                     if(Rlist&0b10){memcontrol(pos,true,R[1],4);pos=pos+4;}
                     if(Rlist&0b1){memcontrol(pos,true,R[0],4);pos=pos+4;}
                     R[Rn]=pos;
                     break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                 case 0B1000:
                     if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos-4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos-4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos-4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos-4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos-4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos-4;memcontrol(pos,true,R[0],4);}
                     break;
                 case 0B1001:
                     if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos-4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos-4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos-4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos-4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos-4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos-4;memcontrol(pos,true,R[0],4);}
                     R[Rn]=pos;
                     break;
                 case 0B1010://模式
                     if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos-4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos-4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos-4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos-4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos-4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos-4;memcontrol(pos,true,R[0],4);}
                     break;
                 case 0B1011:
                     if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos-4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos-4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos-4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos-4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos-4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos-4;memcontrol(pos,true,R[0],4);}
                     R[Rn]=pos;
                     break;
                 case 0B1100:
                     if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos+4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos+4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos+4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos+4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos+4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos+4;memcontrol(pos,true,R[0],4);}
                     break;
                 case 0B1101:
                     if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos+4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos+4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos+4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos+4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos+4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos+4;memcontrol(pos,true,R[0],4);}
                     R[Rn]=pos;
                     break;
                 case 0B1110://模式
                     if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos+4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos+4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos+4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos+4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos+4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos+4;memcontrol(pos,true,R[0],4);}
                     break;
                 case 0B1111://模式
                     if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,true,R[15],4);}
                     if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,true,R[14],4);}
                     if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,true,R[13],4);}
                     if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,true,R[12],4);}
                     if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,true,R[11],4);}
                     if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,true,R[10],4);}
                     if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,true,R[9],4);}
                     if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,true,R[8],4);}
                     if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,true,R[7],4);}
                     if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,true,R[6],4);}
                     if(Rlist&0b100000){pos=pos+4;memcontrol(pos,true,R[5],4);}
                     if(Rlist&0b10000){pos=pos+4;memcontrol(pos,true,R[4],4);}
                     if(Rlist&0b1000){pos=pos+4;memcontrol(pos,true,R[3],4);}
                     if(Rlist&0b100){pos=pos+4;memcontrol(pos,true,R[2],4);}
                     if(Rlist&0b10){pos=pos+4;memcontrol(pos,true,R[1],4);}
                     if(Rlist&0b1){pos=pos+4;memcontrol(pos,true,R[0],4);}
                     R[Rn]=pos;
                     break;
                 default:
                     printf("load default 、\n");
                     break;
                 }
                // printf("li ji shuo %x\n",R[3]);
         }
         else{// STM         stm ssssssssssssssssssssssssssss
             //printf("STM\n");
             // p=1先减去后传 u=0减 s=0不载入psr或者user模式  w=1写回基地址
              switch ((IR>>21)&15){
                  //pusw
              case 0B0000:
                  //先传后减 不歇会
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos-4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos-4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos-4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos-4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos-4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos-4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos-4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos-4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos-4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos-4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos-4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos-4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos-4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos-4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos-4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos-4;}
                  break;
              case 0B0001:
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos-4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos-4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos-4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos-4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos-4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos-4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos-4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos-4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos-4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos-4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos-4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos-4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos-4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos-4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos-4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos-4;}
                  R[Rn]=pos;
                  break;
              case 0B0010://模式
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos-4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos-4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos-4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos-4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos-4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos-4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos-4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos-4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos-4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos-4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos-4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos-4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos-4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos-4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos-4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos-4;}
                  break;
              case 0B0011://模式
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos-4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos-4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos-4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos-4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos-4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos-4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos-4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos-4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos-4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos-4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos-4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos-4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos-4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos-4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos-4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos-4;}
                  R[Rn]=pos;
                  break;
              case 0B0100:
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos+4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos+4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos+4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos+4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos+4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos+4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos+4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos+4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos+4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos+4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos+4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos+4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos+4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos+4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos+4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos+4;}
                  break;
              case 0B0101:
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos+4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos+4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos+4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos+4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos+4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos+4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos+4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos+4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos+4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos+4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos+4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos+4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos+4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos+4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos+4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos+4;}
                  R[Rn]=pos;
                  break;
              case 0B0110://模式
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos+4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos+4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos+4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos+4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos+4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos+4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos+4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos+4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos+4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos+4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos+4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos+4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos+4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos+4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos+4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos+4;}
                  break;
              case 0B0111:
                  if(Rlist&0b1){memcontrol(pos,false,R[0],4);pos=pos+4;}
                  if(Rlist&0b10){memcontrol(pos,false,R[1],4);pos=pos+4;}
                  if(Rlist&0b100){memcontrol(pos,false,R[2],4);pos=pos+4;}
                  if(Rlist&0b1000){memcontrol(pos,false,R[3],4);pos=pos+4;}
                  if(Rlist&0b10000){memcontrol(pos,false,R[4],4);pos=pos+4;}
                  if(Rlist&0b100000){memcontrol(pos,false,R[5],4);pos=pos+4;}
                  if(Rlist&0b1000000){memcontrol(pos,false,R[6],4);pos=pos+4;}
                  if(Rlist&0b10000000){memcontrol(pos,false,R[7],4);pos=pos+4;}
                  if(Rlist&0b100000000){memcontrol(pos,false,R[8],4);pos=pos+4;}
                  if(Rlist&0b1000000000){memcontrol(pos,false,R[9],4);pos=pos+4;}
                  if(Rlist&0b10000000000){memcontrol(pos,false,R[10],4);pos=pos+4;}
                  if(Rlist&0b100000000000){memcontrol(pos,false,R[11],4);pos=pos+4;}
                  if(Rlist&0b1000000000000){memcontrol(pos,false,R[12],4);pos=pos+4;}
                  if(Rlist&0b10000000000000){memcontrol(pos,false,R[13],4);pos=pos+4;}
                  if(Rlist&0b100000000000000){memcontrol(pos,false,R[14],4);pos=pos+4;}
                  if(Rlist&0b1000000000000000){memcontrol(pos,false,R[15],4);pos=pos+4;}
                  R[Rn]=pos;
                  break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
              case 0B1000:
                  if(Rlist&0b1){pos=pos-4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos-4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos-4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos-4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos-4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos-4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,false,R[15],4);}
                  break;
              case 0B1001:
                  if(Rlist&0b1){pos=pos-4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos-4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos-4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos-4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos-4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos-4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,false,R[15],4);}
                  R[Rn]=pos;
                  break;
              case 0B1010://模式
                  if(Rlist&0b1){pos=pos-4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos-4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos-4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos-4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos-4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos-4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,false,R[15],4);}
                  break;
              case 0B1011:
                  if(Rlist&0b1){pos=pos-4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos-4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos-4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos-4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos-4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos-4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos-4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos-4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos-4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos-4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos-4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos-4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos-4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos-4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos-4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos-4;memcontrol(pos,false,R[15],4);}
                  R[Rn]=pos;
                  break;
              case 0B1100:
                  if(Rlist&0b1){pos=pos+4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos+4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos+4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos+4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos+4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos+4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,false,R[15],4);}
                  break;
              case 0B1101:
                  if(Rlist&0b1){pos=pos+4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos+4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos+4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos+4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos+4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos+4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,false,R[15],4);}
                  R[Rn]=pos;
                  break;
              case 0B1110://模式
                  if(Rlist&0b1){pos=pos+4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos+4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos+4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos+4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos+4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos+4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,false,R[15],4);}
                  break;
              case 0B1111://模式
                  if(Rlist&0b1){pos=pos+4;memcontrol(pos,false,R[0],4);}
                  if(Rlist&0b10){pos=pos+4;memcontrol(pos,false,R[1],4);}
                  if(Rlist&0b100){pos=pos+4;memcontrol(pos,false,R[2],4);}
                  if(Rlist&0b1000){pos=pos+4;memcontrol(pos,false,R[3],4);}
                  if(Rlist&0b10000){pos=pos+4;memcontrol(pos,false,R[4],4);}
                  if(Rlist&0b100000){pos=pos+4;memcontrol(pos,false,R[5],4);}
                  if(Rlist&0b1000000){pos=pos+4;memcontrol(pos,false,R[6],4);}
                  if(Rlist&0b10000000){pos=pos+4;memcontrol(pos,false,R[7],4);}
                  if(Rlist&0b100000000){pos=pos+4;memcontrol(pos,false,R[8],4);}
                  if(Rlist&0b1000000000){pos=pos+4;memcontrol(pos,false,R[9],4);}
                  if(Rlist&0b10000000000){pos=pos+4;memcontrol(pos,false,R[10],4);}
                  if(Rlist&0b100000000000){pos=pos+4;memcontrol(pos,false,R[11],4);}
                  if(Rlist&0b1000000000000){pos=pos+4;memcontrol(pos,false,R[12],4);}
                  if(Rlist&0b10000000000000){pos=pos+4;memcontrol(pos,false,R[13],4);}
                  if(Rlist&0b100000000000000){pos=pos+4;memcontrol(pos,false,R[14],4);}
                  if(Rlist&0b1000000000000000){pos=pos+4;memcontrol(pos,false,R[15],4);}
                  R[Rn]=pos;
                  break;
              default:
                  printf("load default 、\n");
                  break;
              }
                 //printf("li ji shuo str%x\n",Member[pos+2]);
             }

}

