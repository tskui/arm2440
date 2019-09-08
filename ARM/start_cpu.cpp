#include <start_cpu.h>
#include <data.h>
#include "FUNCMD.h"
#include "mythread.h"
volatile quint8 Member[1024*4]={0};
volatile quint8 SFR_MEM[0X60000000-0X48000000]={0};
quint32  IR=0;
volatile quint32 R[16]={0};
volatile quint32 R_FIQ[16]={0};
volatile quint32 R_IRQ[16]={0};
#define  SP R[13]
#define  LR R[14]
#define  PC R[15]
quint32 CYC_BUFFER=0;
volatile quint32 CPSR=0;//程序状态寄存器N Z C V Q DNM(RAZ) I F T M4 M3 M2 M1 M0
volatile quint32 SPSR_FIQ=0;//程序状态保存寄存器
volatile quint32 SPSR_IRQ =0;//程序状态保存寄存器
volatile quint32 SPSR_SUPERVISOR =0;//程序状态保存寄存器
volatile quint32 SPSR_ABORT =0;//程序状态保存寄存器
volatile quint32 SPSR_UNDEFINEED =0;//程序状态保存寄存器
quint32 loadbin(){
    QFile file("C:\\Users\\Administrator\\Desktop\\a\\armtest\\pro1.bin");
    if (!file.open(QIODevice::ReadOnly))
    {   printf("fail 、\n");
        return 0;
    }
    QDataStream in(&file);

    in.setVersion(QDataStream::Qt_5_1);
    quint32 i=0,j=3,n=0;
    while (!file.atEnd()) {
        n+=in.readRawData((char*)&Member[i+j],sizeof(quint8));j--;
            if(j==-1){j=3;i=i+4;}
          }
    printf("%d\n",n);
    return n;
}
void fetch_instruction(){
    printf("PC=%x\n",PC);
    IR=(Member[PC]<<24)+(Member[PC+1]<<16)+(Member[PC+2]<<8)+Member[PC+3];
    PC=PC+4;
}
void Analysis_instruction(){
    qint8 codetype=(IR>>25)&7;
    qint8 operation=(IR>>21)&15;
    CYC_BUFFER=0;
    switch (codetype) {
    case 0:
        printf("duo zhiling register\n");
        if((0b1001==operation)&&(((IR>>4)&15)==1)){
            printf("branchx \n");
            bx(IR);
        }
        if(0b0000==operation){
            printf("and");
            and0(IR);
        }
        if(0b0001==operation){

            printf("eor");
        }
        if(0b0010==operation){
            printf("sub");
            sub0(IR);
        }
        if(0b0011==operation){
            printf("rsb");
        }
        if(0b0100==operation){
            printf("add");
            add0(IR);
        }
        if(0b0101==operation){
            printf("adc");
        }
        if(0b0110==operation){
            printf("sbc");
        }
        if(0b0111==operation){
            printf("rsc");
        }
        if(0b1000==operation){
            printf("tst");
        }
        if(0b1001==operation){
            printf("teq");
        }
        if(0b1010==operation){
            printf("cmp\n");
            cmp(IR);
        }
        if(0b1011==operation){
            printf("cmn");
        }
        if(0b1100==operation){
            printf("orr");
            orr0(IR);
        }
        if(0b1101==operation){
            mov(IR);
            printf("mov\n");
        }
        if(0b1110==operation){
            printf("bic\n");
            bic0(IR);
        }
        if(0b1111==operation){
            printf("mvn");
        }

        break;
    case 1:// 立即数
        printf("Data/processing/PSR Transfer\n");
        if(0b1101==operation){
            cyc_right(((IR>>8)&15));
            R[(IR>>12)&15]=CYC_BUFFER;
            printf("%d\n",R[(IR>>12)&15]);
            printf("li ji shu mov \n");
        }
        if(0b0010==operation){
            printf("sub \n");
        }
        if(0b1110==operation){
            printf("bic\n");
            bic1(IR);
        }
        if(0b1100==operation){
            printf("orr\n");
            orr1(IR);
        }
        if(0b1010==operation){
            printf("cmp\n");
            cmp(IR);
        }
        if(0b0000==operation){
            printf("and1");
            and1(IR);
        }
        if(0b0100==operation){
            printf("add");
            add1(IR);
        }
        if(0b0010==operation){
            printf("sub");
            sub1(IR);
        }
        break;
    case 2:
        printf("STR/LDR Transfer LI JI SHUO\n");
        LDR_STR(IR);
        break;
    case 3:
        printf("single Data Transfer STR/LDR Transfer JI CUN QI\n");
        LDR_STR(IR);
        break;
    case 4:
        printf("block data Transfer\n");
        break;
    case 5:
        printf("branch 5\n");
        b(IR);
        break;
    case 6:
        printf("coprocessor data Transfer\n");
        break;
    case 7:
        printf("coprocessor data operation/register transter\n");
        break;
    default:
        printf("default!\n");
        break;
    }
    printf("%d\n",codetype);
}
void memcontrol(quint32 addr,bool isread,quint32 & taget,quint8 size=4){
    if(addr<0x08000000){
        //bank0
        if(isread){
            if(size==1){
                taget=Member[addr+3];
            }
            else{//默认大段模式
            taget=(quint32)Member[addr]<<24|Member[addr+1]<<16|Member[addr+2]<<8|Member[addr+3];}
            }
       else{
             if(size==1){
                Member[addr+3]=taget&255;
               }
             else{
             Member[addr+3]=taget&255;
             Member[addr+2]=(taget>>8)&255;
             Member[addr+1]=(taget>>16)&255;
             Member[addr]=(taget>>24)&255;}
        }
        return;
    }
    if(addr<0x10000000){
        return;
    }
    if(addr<0x18000000){
        return;
    }
    if(addr<0x20000000){
        return;
    }
    if(addr<0x28000000){
        return;
    }
    if(addr<0x30000000){

        return;
    }
    if(addr<0x38000000){
        if(thread0::fnand!=NULL&&thread0::fnand->isOpen()){
          thread0::fnand->reset();
          //QDataStream in(thread0::fnand);
          if(thread0::fnand->seek(addr-0x30000000)){
             char str[4]={0,0,0,0};
             if(isread){
                  thread0::fnand->read(str,4);
                  //in.readRawData(str,4);
                  if(size==1){
                      taget=str[3];
                  }
                  else{//默认大段模式
                      taget=((quint32)str[0]<<24)|(str[1]<<16)|(str[2]<<8)|(str[3]);}
                  }
             else{
                   if(size==1){
                      str[3]=taget&255;
                      thread0::fnand->write(str,4);
                      thread0::fnand->flush();
                      //in.writeRawData(str,4);
                      //thread0::fnand->flush();
                    }else{
                      str[3]=taget&255;
                      str[2]=(taget>>8)&255;
                      str[1]=(taget>>16)&255;
                      str[0]=(taget>>24)&255;
                      thread0::fnand->write(str,4);
                      thread0::fnand->flush();
                      //in.writeRawData(str,4);
                      //thread0::fnand->flush();

                   }
              }
          }
        }
        return;
    }
    if(addr<0x40000000){
        return;
    }
    if(addr<0x40000fff){
        return;
    }
    if(addr>0x48000000&&addr<0x60000000){
        addr=addr-0x48000000;
        if(isread){
            if(size==1){
                taget=SFR_MEM[addr+3];
            }else{
                taget=(quint32)SFR_MEM[addr]<<24|SFR_MEM[addr+1]<<16|SFR_MEM[addr+2]<<8|SFR_MEM[addr+3];
            }
         }
        else{
            if(size==1){
             SFR_MEM[addr+3]=taget&255;}
            else{
             SFR_MEM[addr+3]=taget&255;
             SFR_MEM[addr+2]=(taget>>8)&255;
             SFR_MEM[addr+1]=(taget>>16)&255;
             SFR_MEM[addr]=(taget>>24)&255;}
        }
        return;
    }

}
