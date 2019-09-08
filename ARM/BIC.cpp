#include <QCoreApplication>
#include <C_SPSR.h>
extern quint32 R[16];
//extern quint8 Member[1024*1024*1024];
extern quint32 CYC_BUFFER;
void bic0(quint32 IR){
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
        //printf("register \n");
        if(0==((IR>>4)&1)){//数移动
            switch ((IR>>5)&3) {
            case 0://lsl
                R[(IR>>12)&15]=(R[(IR>>16)&15])&(~(R[IR&15]<<((IR>>7)&0B11111)));
                break;
            case 1://lsr
                R[(IR>>12)&15]=(R[(IR>>16)&15])&(~(R[IR&15]>>((IR>>7)&0B11111)));
                break;
            case 2://ar
                //printf("arithmetic right\n");
                break;
            case 3://ror
                CYC_BUFFER=R[IR&15];
                CYC_BUFFER=CYC_BUFFER<<(32-((IR>>7)&0B11111)-((IR>>7)&0B11111));
                CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(((IR>>7)&0B11111)+((IR>>7)&0B11111)));
                CYC_BUFFER=~CYC_BUFFER;
                R[(IR>>12)&15]=R[(IR>>16)&15]&CYC_BUFFER;
                break;
            default:
                //printf("default bic \n");
                break;
            }
        }
        else{
            switch ((IR>>5)&3) {
            case 0://lsl
                R[(IR>>12)&15]=(R[(IR>>16)&15])&(~(R[IR&15]<<(R[(IR>>8)&15])));
                break;
            case 1://lsr
                R[(IR>>12)&15]=(R[(IR>>16)&15])&(~(R[IR&15]>>(R[(IR>>8)&15])));
                break;
            case 2://ar
                //printf("arithmetic right\n");
                break;
            case 3://ror
                CYC_BUFFER=R[IR&15];
                CYC_BUFFER=CYC_BUFFER<<(32-(R[(IR>>8)&15])-(R[(IR>>8)&15]));
                CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>((R[(IR>>8)&15])+(R[(IR>>8)&15])));
                CYC_BUFFER=~CYC_BUFFER;
                R[(IR>>12)&15]=R[(IR>>16)&15]&CYC_BUFFER;
                break;
            default:
                //printf("default bic \n");
                break;
            }
        }
}
void bic1(quint32 IR){
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
    CYC_BUFFER=~CYC_BUFFER;
    R[(IR>>12)&15]=R[(IR>>16)&15]&CYC_BUFFER;
}
/*
   MOV R1,#2_111
   mov r2,#2_001
   BIC R1,R1,#2_001
   BIC R1,R1,R3,lsl 1
   BIC  R0,R0,#0xF0000000
   bic r3,r1,r2, lsl #1
   bic r4,r1,r2, lsr #1
   bic r5,r1,r3, lsr r2
*/
