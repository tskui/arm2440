#include <QCoreApplication>
#include "C_SPSR.h"
#include <QDebug>
extern quint32 R[16];
extern quint32 CYC_BUFFER;
void tst0(quint32 IR){
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
    if(0==((IR>>4)&1)){//数移动
        switch ((IR>>5)&3) {
        case 0://lsl
            if((R[(IR>>16)&15])&((R[IR&15]<<((IR>>7)&0B11111)))){
                 CPSR=CPSR&0xBFFFFFFF;
            }
            else{
                 CPSR=CPSR|0x40000000;
            }
            break;
        case 1://lsr
            if((R[(IR>>16)&15])&((R[IR&15]>>((IR>>7)&0B11111)))){
                 CPSR=CPSR&0xBFFFFFFF;
            }else{
                 CPSR=CPSR|0x40000000;
            }
            break;
        case 2://ar
            printf("arithmetic right\n");
            break;
        case 3://ror
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER<<(32-((IR>>7)&0B11111)-((IR>>7)&0B11111));
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(((IR>>7)&0B11111)+((IR>>7)&0B11111)));
            if(R[(IR>>16)&15]&CYC_BUFFER){
                CPSR=CPSR&0xBFFFFFFF;
            }else{
                CPSR=CPSR|0x40000000;
            }
            break;
        default:
            printf("default orr \n");
            break;
        }
    }
    else{
        switch ((IR>>5)&3) {
        case 0://lsl
            if((R[(IR>>16)&15])&((R[IR&15]<<(R[(IR>>8)&15])))){
               CPSR=CPSR&0xBFFFFFFF;
            }else{
               CPSR=CPSR|0x40000000;
            }
            break;
        case 1://lsr
            if((R[(IR>>16)&15])&((R[IR&15]>>(R[(IR>>8)&15])))){
               CPSR=CPSR&0xBFFFFFFF;
            }else{
               CPSR=CPSR|0x40000000;
            }
            break;
        case 2://ar
            printf("arithmetic right\n");
            break;
        case 3://ror
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER<<(32-(R[(IR>>8)&15])-(R[(IR>>8)&15]));
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>((R[(IR>>8)&15])+(R[(IR>>8)&15])));
            if(R[(IR>>16)&15]&CYC_BUFFER){
               CPSR=CPSR&0xBFFFFFFF;
            }else{
               CPSR=CPSR|0x40000000;
            }
            break;
        default:
            printf("default orr \n");
            break;
        }
    }
}
void tst1(quint32 IR){
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
    CYC_BUFFER=(IR&255);
    CYC_BUFFER=CYC_BUFFER<<(32-((IR>>8)&15)-((IR>>8)&15));
    CYC_BUFFER=CYC_BUFFER|((IR&255)>>(((IR>>8)&15)+((IR>>8)&15)));
    if(R[(IR>>16)&15]&CYC_BUFFER){
     CPSR=CPSR&0xBFFFFFFF;
    }else{
     CPSR=CPSR|0x40000000;
    }
}
