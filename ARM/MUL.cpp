#include <QCoreApplication>
extern quint32 R[16];
//extern quint8 Member[1024*1024*1024];
extern quint32 CYC_BUFFER;
void mul0(quint32 IR){//寄存器
    if(0==((IR>>4)&1)){//数移动
        switch ((IR>>5)&3) {
        case 0://lsl
            R[(IR>>12)&15]=(R[(IR>>16)&15])*((R[IR&15]<<((IR>>7)&0B11111)));
            break;
        case 1://lsr
            R[(IR>>12)&15]=(R[(IR>>16)&15])*((R[IR&15]>>((IR>>7)&0B11111)));
            break;
        case 2://ar
            printf("arithmetic right\n");
            break;
        case 3://ror
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER<<(32-((IR>>7)&0B11111)-((IR>>7)&0B11111));
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>(((IR>>7)&0B11111)+((IR>>7)&0B11111)));
            R[(IR>>12)&15]=R[(IR>>16)&15]*CYC_BUFFER;
            break;
        default:
            printf("default mul0 \n");
            break;
        }
    }
    else{
        switch ((IR>>5)&3) {
        case 0://lsl
            R[(IR>>12)&15]=(R[(IR>>16)&15])*((R[IR&15]<<(R[(IR>>8)&15])));
            break;
        case 1://lsr
            R[(IR>>12)&15]=(R[(IR>>16)&15])*((R[IR&15]>>(R[(IR>>8)&15])));
            break;
        case 2://ar
            printf("arithmetic right\n");
            break;
        case 3://ror
            CYC_BUFFER=R[IR&15];
            CYC_BUFFER=CYC_BUFFER<<(32-(R[(IR>>8)&15])-(R[(IR>>8)&15]));
            CYC_BUFFER=CYC_BUFFER|(R[IR&15]>>((R[(IR>>8)&15])+(R[(IR>>8)&15])));
            R[(IR>>12)&15]=R[(IR>>16)&15]*CYC_BUFFER;
            break;
        default:
            printf("default mul0 \n");
            break;
        }
    }
         //printf("R[(IR>>12)&15]=%d\n",R[(IR>>12)&15]);
}
void mul1(quint32 IR){//立即数
    CYC_BUFFER=(IR&255);
    CYC_BUFFER=CYC_BUFFER<<(32-((IR>>8)&15)-((IR>>8)&15));
    CYC_BUFFER=CYC_BUFFER|((IR&255)>>(((IR>>8)&15)+((IR>>8)&15)));
    R[(IR>>12)&15]=R[(IR>>16)&15]*CYC_BUFFER;
    //printf("R[(IR>>12)&15]=%d\n",R[(IR>>12)&15]);

}

