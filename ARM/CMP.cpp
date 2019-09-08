#include <QCoreApplication>
#include <C_SPSR.h>
#include <QDebug>
extern quint32 R[16];
//extern quint8 Member[1024*1024*1024];
extern quint32 CYC_BUFFER;
void cmp(quint32 IR){
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
    CPSR=CPSR&0X00FFFFFF;
    quint32 RN=R[(IR>>16)&15];
    //asm("movl %ax,10");
    if(0b001==((IR>>25)&7)){//立即数
        CYC_BUFFER=(quint32)(IR&255);
        CYC_BUFFER=CYC_BUFFER<<(32-((IR>>8)&15)-((IR>>8)&15));
        CYC_BUFFER=CYC_BUFFER|((IR&255)>>(((IR>>8)&15)+((IR>>8)&15)));
        qint32 result=(qint32)(RN-CYC_BUFFER);

        //__asm__ __volatile__("movl %0,%%eax;movl %1,%%ebx;cmp %%eax,%%ebx;mov %%EFLAGS,%2":"=r"(RN),"=r"(CYC_BUFFER):"r"(mypsw):"eax","ebx");
        if(result==0){SET_CPSR_Z_1;}else{ SET_CPSR_Z_0;}//N Z C V
        if(result>=0){SET_CPSR_N_0;}else{ SET_CPSR_N_1;}
        if(RN<CYC_BUFFER){SET_CPSR_C_0;}else{ SET_CPSR_C_1;}
        SET_CPSR_V_0;
        //qDebug()<<"___"+QString::number((CPSR>>28)&15);

    }
    else{//register
        qint32 result=0;
        if(0==((IR>>4)&1)){//数移动
            switch ((IR>>5)&3) {
            case 0://lsl
                result=RN-(R[IR&15]<<((IR>>7)&0B11111));
                break;
            case 1://lsr
                result=RN-(R[IR&15]>>((IR>>7)&0B11111));
                break;
            case 2://ar
                //printf("arithmetic right\n");
                break;
            case 3://ror
                CYC_BUFFER=R[IR&15];
                CYC_BUFFER=CYC_BUFFER<<(32-((IR>>7)&0B11111)-((IR>>7)&0B11111));
                CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(((IR>>7)&0B11111)+((IR>>7)&0B11111)));
                result=RN-CYC_BUFFER;
                break;
            default:
                printf("default bic \n");
                break;
            }
            if(result==0){SET_CPSR_Z_1;}else{ SET_CPSR_Z_0;}
            if(result>=0) {SET_CPSR_N_0;}else{ SET_CPSR_N_1;}
            if(result<0) {SET_CPSR_C_0;}else{ SET_CPSR_C_1;}
            SET_CPSR_V_0;
        }
        else{
            switch ((IR>>5)&3) {
            case 0://lsl
                result=RN-(R[IR&15]<<(R[(IR>>8)&15]));
                break;
            case 1://lsr
                result=RN-(R[IR&15]>>(R[(IR>>8)&15]));
                break;
            case 2://ar
                //printf("arithmetic right\n");
                break;
            case 3://ror
                CYC_BUFFER=R[IR&15];
                CYC_BUFFER=CYC_BUFFER<<(32-(R[(IR>>8)&15])-(R[(IR>>8)&15]));
                CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>((R[(IR>>8)&15])+(R[(IR>>8)&15])));
                result=RN-CYC_BUFFER;
                break;
            default:
                //printf("default bic \n");
                break;
            }
            if(result==0){SET_CPSR_Z_1;}else{ SET_CPSR_Z_0;}
            if(result>=0) {SET_CPSR_N_0;}else{ SET_CPSR_N_1;}
            if(result<0) {SET_CPSR_C_0;}else{ SET_CPSR_C_1;}
        }

    }
     //printf("%x_\n",CPSR);

}
