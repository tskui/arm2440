#include <data.h>
#include <QCoreApplication>
#include "C_SPSR.h"
#include <QDebug>
extern  bool isjump;
extern quint32 R[16];
void mov(quint32 IR){
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

    if(((IR>>12)&15)==15)isjump=true;
    if(0==(IR&0b010000)){//立即数
        switch ((IR>>5)&3) {
        case LSL:
            R[(IR>>12)&15]=R[IR&15]<<((IR>>7)&0B11111);
            break;
        case LSR:
            R[(IR>>12)&15]=R[IR&15]>>((IR>>7)&0B11111);
            break;
        case ASL:
            printf("no define \n");
            break;
        case ROR:
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER<<(32-((IR>>7)&0B11111)-((IR>>7)&0B11111));
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(((IR>>7)&0B11111)+((IR>>7)&0B11111)));
            R[(IR>>12)&15]=CYC_BUFFER;
            break;
        default:
            printf("mov default \n");
            break;
        };
    }
    else{
        switch ((IR>>5)&3) {
        case LSL:
            R[(IR>>12)&15]=R[IR&15]<<R[(IR>>8)&15];
            break;
        case LSR:
            R[(IR>>12)&15]=R[IR&15]>>R[(IR>>8)&15];
            break;
        case ASL:
            printf("no define \n");
            break;
        case ROR:
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER>>(32-R[(IR>>8)&15]-R[(IR>>8)&15]);
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(R[(IR>>8)&15]+R[(IR>>8)&15]));
            R[(IR>>12)&15]=CYC_BUFFER;
            R[(IR>>12)&15]=CYC_BUFFER;
            break;
        default:
            printf("mov default \n");
            break;
        };

    }

}
void movimm(quint32 IR){
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
    cyc_right(((IR>>8)&15));
    R[(IR>>12)&15]=CYC_BUFFER;
    //printf("%d\n",R[(IR>>12)&15]);
}
