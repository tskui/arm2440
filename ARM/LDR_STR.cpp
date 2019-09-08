#include <QCoreApplication>
#include <C_SPSR.h>
#include <QDebug>
extern quint32 R[16];
void memcontrol(quint32 addr,bool isread,quint32 & taget,quint8 size=4);
void LDR_STR(quint32 IR)
{
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
    quint32 pos=0,Rn=((IR>>16)&15),Rd=((IR>>12)&15),Offset=((IR)&0b111111111111),Mdata=0;
    quint32 Rm=(IR&15);
    pos=R[Rn];
    if(1==((IR>>20)&1)){//load
        //printf("load_\n");
        if(0==((IR>>25)&1)){ // OFFSET 为立即数
           // p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
            switch ((IR>>21)&15){
                //pubw
            case 0B0000:
                //先传后减不歇会
                //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rd]=Mdata;
                break;
            case 0B0001:
               // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rd]=Mdata;
                pos=pos-Offset;
                R[Rn]=pos;
                break;
            case 0B0010:
                //Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata;
                break;
            case 0B0011:
                //Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata&255;
                pos=pos-Offset;
                R[Rn]=pos;
                break;
            case 0B0100:
               // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rd]=Mdata;
                break;
            case 0B0101:
                //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rd]=Mdata;
                pos=pos+Offset;
                R[Rn]=pos;
                break;
            case 0B0111:
                break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
            case 0B1000:
                pos=pos-Offset;
               // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rd]=Mdata;
                break;
            case 0B1001:
                pos=pos-Offset;
                //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rn]=pos;
                R[Rd]=Mdata;
                break;
            case 0B1010:
                pos=pos-Offset;
                //Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata&255;
                break;
            case 0B1011:
                pos=pos-Offset;
               // Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata&255;
                R[Rn]=pos;
                break;
            case 0B1100:
                 pos=pos+Offset;
                 //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                 memcontrol(pos,true,Mdata,4);
                 R[Rd]=Mdata;
                break;
            case 0B1101:
                pos=pos+Offset;
                //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                memcontrol(pos,true,Mdata,4);
                R[Rn]=pos;
                R[Rd]=Mdata;
                break;
            case 0B1110:
                pos=pos+Offset;
               // Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata&255;

                break;
            case 0B1111:
                pos=pos+Offset;
                //Mdata=Member[pos];
                memcontrol(pos,true,Mdata,1);
                R[Rd]=Mdata&255;
                 R[Rn]=pos;
                break;
            default:
                printf("load default 、\n");
                break;
            }
           // printf("li ji shuo %x\n",R[3]);
        }
        else{  //寄存器
            if(0==((IR>>4)&1)){//立即说移动

                switch ((IR>>5)&3) {
                case 0B00:
                    Offset=R[Rm]<<((IR>>7)&0B11111);
                    break;
                case 0B01:
                    Offset=R[Rm]>>((IR>>7)&0B11111);
                    break;
                case 0B10:
                  break;
                case 0B11:
                    Offset=(R[Rm]>>((IR>>7)&0B11111))|(R[Rm]<<((32-(IR>>7))&0B11111));
                    break;
                default:
                    break;
                }
//                             ....
                switch ((IR>>21)&15){
                    //pubw
                case 0B0000:
                    //先传后减不歇会
                    //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rd]=Mdata;
                    break;
                case 0B0001:
                   // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rd]=Mdata;
                    pos=pos-Offset;
                    R[Rn]=pos;
                    break;
                case 0B0010:
                    //Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata&255;
                    break;
                case 0B0011:
                    //Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata;
                    pos=pos-Offset;
                    R[Rn]=pos;
                    break;
                case 0B0100:
                    //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rd]=Mdata;
                    break;
                case 0B0101:
                    //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rd]=Mdata;
                    pos=pos+Offset;
                    R[Rn]=pos;
                    break;
                case 0B0111:
                    break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                case 0B1000:
                    pos=pos-Offset;
                    //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rd]=Mdata;
                    break;
                case 0B1001:
                    pos=pos-Offset;
                    //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rn]=pos;
                    R[Rd]=Mdata;
                    break;
                case 0B1010:
                    pos=pos-Offset;
                    //Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata;
                    break;
                case 0B1011:
                    pos=pos-Offset;
                   // Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata;
                    R[Rn]=pos;
                    break;
                case 0B1100:
                     pos=pos+Offset;
                     //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                     memcontrol(pos,true,Mdata,4);
                     R[Rd]=Mdata;
                    break;
                case 0B1101:
                    pos=pos+Offset;
                   // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
                    memcontrol(pos,true,Mdata,4);
                    R[Rn]=pos;
                    R[Rd]=Mdata;
                    break;
                case 0B1110:
                    pos=pos+Offset;
                    //Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata;

                    break;
                case 0B1111:
                    pos=pos+Offset;
                    //Mdata=Member[pos];
                    memcontrol(pos,true,Mdata,1);
                    R[Rd]=Mdata;
                    R[Rn]=pos;
                    break;
                default:
                    printf("load default 、\n");
                    break;
                }
            }
            else{
                printf("no default 、n\n");
            }
        }
        //printf("rsg _%d\n",R[Rd]);
    }
    else{// STR          str ssssssssssssssssssssssssssss
        //printf("STR\n");
       Mdata=R[Rd];
        if(0==((IR>>25)&1)){ // OFFSET 为立即数
            switch ((IR>>21)&15){
                //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
            case 0B0000:
                //先传后减去子传输不写回
                /*Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos+0]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                break;
            case 0B0001:
                //先传后减字传输写回
                /*Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos+0]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                R[Rn]=pos-Offset;
                break;
            case 0B0010:
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                break;
            case 0B0011:
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                R[Rn]=pos-Offset;
                break;
                //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
            case 0B0100:
                /*Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos+0]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                break;
            case 0B0101:
               /* Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos+0]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                R[Rn]=pos+Offset;
                break;
            case 0B0111:
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                R[Rn]=pos+Offset;
                break;
            case 0B1000://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                pos=pos-Offset;
               /* Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos+0]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                break;
            case 0B1001:
                pos=pos-Offset;
                /*Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                R[Rn]=pos;
                break;
            case 0B1010:
                pos=pos-Offset;
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                break;
            case 0B1011:
                pos=pos-Offset;
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                R[Rn]=pos;
                break;
            case 0B1100://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                 pos=pos+Offset;
                 /*Member[pos+3]=(R[Rd]&255);
                 Member[pos+2]=((R[Rd]>>8)&255);
                 Member[pos+1]=((R[Rd]>>16)&255);
                 Member[pos]=((R[Rd]>>24)&255);*/
                 memcontrol(pos,false,Mdata,4);
                break;
            case 0B1101:
                pos=pos+Offset;
                /*Member[pos+3]=(R[Rd]&255);
                Member[pos+2]=((R[Rd]>>8)&255);
                Member[pos+1]=((R[Rd]>>16)&255);
                Member[pos]=((R[Rd]>>24)&255);*/
                memcontrol(pos,false,Mdata,4);
                R[Rn]=pos;
                break;
            case 0B1110:
                pos=pos+Offset;
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                break;
            case 0B1111:
                pos=pos+Offset;
                //Member[pos]=(R[Rd]&255);
                memcontrol(pos,false,Mdata,1);
                R[Rn]=pos;
                break;
            default:
                printf("STR default 、\n");
                break;
            }
            //printf("li ji shuo str%x\n",Member[pos+2]);
        }
        else{  //寄存器
            if(0==((IR>>4)&1)){//立即说移动

                switch ((IR>>5)&3) {
                case 0B00:
                    Offset=R[Rm]<<((IR>>7)&0B11111);
                    break;
                case 0B01:
                    Offset=R[Rm]>>((IR>>7)&0B11111);
                    break;
                case 0B10:
                  break;
                case 0B11:
                    Offset=(R[Rm]>>((IR>>7)&0B11111))|(R[Rm]<<((32-(IR>>7))&0B11111));
                    break;
                default:
                    break;
                }
//                             ....
                switch ((IR>>21)&15){
                    //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                case 0B0000:
                    //先传后减去子传输不写回
                    /*Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos+0]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    break;
                case 0B0001:
                    //先传后减字传输写回
                   /* Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos+0]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    R[Rn]=pos-Offset;
                    break;
                case 0B0010:
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    break;
                case 0B0011:
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    R[Rn]=pos-Offset;
                    break;
                    //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                case 0B0100:
                    /*Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos+0]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    break;
                case 0B0101:
                   /* Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos+0]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,1);
                    R[Rn]=pos+Offset;
                    break;
                case 0B0111:
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    R[Rn]=pos+Offset;
                    break;
                case 0B1000://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                    pos=pos-Offset;
                    /*Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos+0]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    break;
                case 0B1001:
                    pos=pos-Offset;
                    /*Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    R[Rn]=pos;
                    break;
                case 0B1010:
                    pos=pos-Offset;
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    break;
                case 0B1011:
                    pos=pos-Offset;
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    R[Rn]=pos;
                    break;
                case 0B1100://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
                     pos=pos+Offset;
                    /* Member[pos+3]=(R[Rd]&255);
                     Member[pos+2]=((R[Rd]>>8)&255);
                     Member[pos+1]=((R[Rd]>>16)&255);
                     Member[pos]=((R[Rd]>>24)&255);*/
                     memcontrol(pos,false,Mdata,4);
                    break;
                case 0B1101:
                    pos=pos+Offset;
                    /*Member[pos+3]=(R[Rd]&255);
                    Member[pos+2]=((R[Rd]>>8)&255);
                    Member[pos+1]=((R[Rd]>>16)&255);
                    Member[pos]=((R[Rd]>>24)&255);*/
                    memcontrol(pos,false,Mdata,4);
                    R[Rn]=pos;
                    break;
                case 0B1110:
                    pos=pos+Offset;
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    break;
                case 0B1111:
                    pos=pos+Offset;
                    //Member[pos]=(R[Rd]&255);
                    memcontrol(pos,false,Mdata,1);
                    R[Rn]=pos;
                    break;
                default:
                    printf("STR default 、\n");
                    break;
                }
               // printf("---li ji shuo %x\n",Member[pos]);


            }
            else{
                //printf("no default 、n\n");

            }

           //printf("rsg str\n");
        }

    }

   // printf("%d,%d,%d,%d,%x\n",Member[base],Member[base+1],Member[base+2],Member[base+3],R[13]);
}
void ldr0(quint32 IR){
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
    quint32 pos=0,Rn=((IR>>16)&15),Rd=((IR>>12)&15),Offset=((IR)&0b111111111111),Mdata=0;
    quint32 Rm=(IR&15);
    pos=R[Rn];
    //立即数
    // p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
     switch ((IR>>21)&15){
         //pubw
     case 0B0000:
         //先传后减不歇会
         //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rd]=Mdata;
         break;
     case 0B0001:
        // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rd]=Mdata;
         pos=pos-Offset;
         R[Rn]=pos;
         break;
     case 0B0010:
         //Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata;
         break;
     case 0B0011:
         //Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata&255;
         pos=pos-Offset;
         R[Rn]=pos;
         break;
     case 0B0100:
        // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rd]=Mdata;
         break;
     case 0B0101:
         //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rd]=Mdata;
         pos=pos+Offset;
         R[Rn]=pos;
         break;
     case 0B0111:
         break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
     case 0B1000:
         pos=pos-Offset;
        // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rd]=Mdata;
         break;
     case 0B1001:
         pos=pos-Offset;
         //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rn]=pos;
         R[Rd]=Mdata;
         break;
     case 0B1010:
         pos=pos-Offset;
         //Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata&255;
         break;
     case 0B1011:
         pos=pos-Offset;
        // Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata&255;
         R[Rn]=pos;
         break;
     case 0B1100:
          pos=pos+Offset;
          //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
          memcontrol(pos,true,Mdata,4);
          R[Rd]=Mdata;
         break;
     case 0B1101:
         pos=pos+Offset;
         //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
         memcontrol(pos,true,Mdata,4);
         R[Rn]=pos;
         R[Rd]=Mdata;
         break;
     case 0B1110:
         pos=pos+Offset;
        // Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata&255;

         break;
     case 0B1111:
         pos=pos+Offset;
         //Mdata=Member[pos];
         memcontrol(pos,true,Mdata,1);
         R[Rd]=Mdata&255;
          R[Rn]=pos;
         break;
     default:
         printf("load default 、\n");
         break;
     }
}
void ldr1(quint32 IR){
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
    quint32 pos=0,Rn=((IR>>16)&15),Rd=((IR>>12)&15),Offset=((IR)&0b111111111111),Mdata=0;
    quint32 Rm=(IR&15);
    pos=R[Rn];
    if(0==((IR>>4)&1)){//立即说移动

        switch ((IR>>5)&3) {
        case 0B00:
            Offset=R[Rm]<<((IR>>7)&0B11111);
            break;
        case 0B01:
            Offset=R[Rm]>>((IR>>7)&0B11111);
            break;
        case 0B10:
          break;
        case 0B11:
            Offset=(R[Rm]>>((IR>>7)&0B11111))|(R[Rm]<<((32-(IR>>7))&0B11111));
            break;
        default:
            break;
        }
//                             ....
        switch ((IR>>21)&15){
            //pubw
        case 0B0000:
            //先传后减不歇会
            //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rd]=Mdata;
            break;
        case 0B0001:
           // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rd]=Mdata;
            pos=pos-Offset;
            R[Rn]=pos;
            break;
        case 0B0010:
            //Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata&255;
            break;
        case 0B0011:
            //Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata;
            pos=pos-Offset;
            R[Rn]=pos;
            break;
        case 0B0100:
            //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rd]=Mdata;
            break;
        case 0B0101:
            //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rd]=Mdata;
            pos=pos+Offset;
            R[Rn]=pos;
            break;
        case 0B0111:
            break;// p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
        case 0B1000:
            pos=pos-Offset;
            //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rd]=Mdata;
            break;
        case 0B1001:
            pos=pos-Offset;
            //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rn]=pos;
            R[Rd]=Mdata;
            break;
        case 0B1010:
            pos=pos-Offset;
            //Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata;
            break;
        case 0B1011:
            pos=pos-Offset;
           // Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata;
            R[Rn]=pos;
            break;
        case 0B1100:
             pos=pos+Offset;
             //Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
             memcontrol(pos,true,Mdata,4);
             R[Rd]=Mdata;
            break;
        case 0B1101:
            pos=pos+Offset;
           // Mdata=(Member[pos]<<24)+(Member[pos+1]<<16)+(Member[pos+2]<<8)+Member[pos+3];
            memcontrol(pos,true,Mdata,4);
            R[Rn]=pos;
            R[Rd]=Mdata;
            break;
        case 0B1110:
            pos=pos+Offset;
            //Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata;

            break;
        case 0B1111:
            pos=pos+Offset;
            //Mdata=Member[pos];
            memcontrol(pos,true,Mdata,1);
            R[Rd]=Mdata;
            R[Rn]=pos;
            break;
        default:
            printf("load default 、\n");
            break;
        }
    }
    else{
        printf("no default 、n\n");
    }

}
void str0(quint32 IR){
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
    quint32 pos=0,Rn=((IR>>16)&15),Rd=((IR>>12)&15),Offset=((IR)&0b111111111111),Mdata=0;
    quint32 Rm=(IR&15);
    pos=R[Rn];
    Mdata=R[Rd];
    // OFFSET 为立即数
         switch ((IR>>21)&15){
             //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
         case 0B0000:
             //先传后减去子传输不写回
             /*Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos+0]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             break;
         case 0B0001:
             //先传后减字传输写回
             /*Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos+0]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             R[Rn]=pos-Offset;
             break;
         case 0B0010:
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             break;
         case 0B0011:
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             R[Rn]=pos-Offset;
             break;
             //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
         case 0B0100:
             /*Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos+0]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             break;
         case 0B0101:
            /* Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos+0]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             R[Rn]=pos+Offset;
             break;
         case 0B0111:
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             R[Rn]=pos+Offset;
             break;
         case 0B1000://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
             pos=pos-Offset;
            /* Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos+0]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             break;
         case 0B1001:
             pos=pos-Offset;
             /*Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             R[Rn]=pos;
             break;
         case 0B1010:
             pos=pos-Offset;
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             break;
         case 0B1011:
             pos=pos-Offset;
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             R[Rn]=pos;
             break;
         case 0B1100://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
              pos=pos+Offset;
              /*Member[pos+3]=(R[Rd]&255);
              Member[pos+2]=((R[Rd]>>8)&255);
              Member[pos+1]=((R[Rd]>>16)&255);
              Member[pos]=((R[Rd]>>24)&255);*/
              memcontrol(pos,false,Mdata,4);
             break;
         case 0B1101:
             pos=pos+Offset;
             /*Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
             R[Rn]=pos;
             break;
         case 0B1110:
             pos=pos+Offset;
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             break;
         case 0B1111:
             pos=pos+Offset;
             //Member[pos]=(R[Rd]&255);
             memcontrol(pos,false,Mdata,1);
             R[Rn]=pos;
             break;
         default:
             printf("STR default 、\n");
             break;
         }
}
void str1(quint32 IR){
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
    quint32 pos=0,Rn=((IR>>16)&15),Rd=((IR>>12)&15),Offset=((IR)&0b111111111111),Mdata=0;
    quint32 Rm=(IR&15);
    pos=R[Rn];
    Mdata=R[Rd];
    if(0==((IR>>4)&1)){//立即说移动

        switch ((IR>>5)&3) {
        case 0B00:
            Offset=R[Rm]<<((IR>>7)&0B11111);
            break;
        case 0B01:
            Offset=R[Rm]>>((IR>>7)&0B11111);
            break;
        case 0B10:
          break;
        case 0B11:
            Offset=(R[Rm]>>((IR>>7)&0B11111))|(R[Rm]<<((32-(IR>>7))&0B11111));
            break;
        default:
            break;
        }
//                             ....
        switch ((IR>>21)&15){
            //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
        case 0B0000:
            //先传后减去子传输不写回
            /*Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos+0]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            break;
        case 0B0001:
            //先传后减字传输写回
           /* Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos+0]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            R[Rn]=pos-Offset;
            break;
        case 0B0010:
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            break;
        case 0B0011:
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            R[Rn]=pos-Offset;
            break;
            //pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
        case 0B0100:
            /*Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos+0]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            break;
        case 0B0101:
           /* Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos+0]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,1);
            R[Rn]=pos+Offset;
            break;
        case 0B0111:
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            R[Rn]=pos+Offset;
            break;
        case 0B1000://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
            pos=pos-Offset;
            /*Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos+0]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            break;
        case 0B1001:
            pos=pos-Offset;
            /*Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            R[Rn]=pos;
            break;
        case 0B1010:
            pos=pos-Offset;
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            break;
        case 0B1011:
            pos=pos-Offset;
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            R[Rn]=pos;
            break;
        case 0B1100://pubw   p=1先减去后传u=0基地址减去 b=0字传输 w=1写回基地址
             pos=pos+Offset;
            /* Member[pos+3]=(R[Rd]&255);
             Member[pos+2]=((R[Rd]>>8)&255);
             Member[pos+1]=((R[Rd]>>16)&255);
             Member[pos]=((R[Rd]>>24)&255);*/
             memcontrol(pos,false,Mdata,4);
            break;
        case 0B1101:
            pos=pos+Offset;
            /*Member[pos+3]=(R[Rd]&255);
            Member[pos+2]=((R[Rd]>>8)&255);
            Member[pos+1]=((R[Rd]>>16)&255);
            Member[pos]=((R[Rd]>>24)&255);*/
            memcontrol(pos,false,Mdata,4);
            R[Rn]=pos;
            break;
        case 0B1110:
            pos=pos+Offset;
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            break;
        case 0B1111:
            pos=pos+Offset;
            //Member[pos]=(R[Rd]&255);
            memcontrol(pos,false,Mdata,1);
            R[Rn]=pos;
            break;
        default:
            printf("STR default 、\n");
            break;
        }
       // printf("---li ji shuo %x\n",Member[pos]);


    }
    else{
        //printf("no default 、n\n");
    }
}
