#include <mythread.h>
#include <QDebug>
#include <QWidget>
#include <mainwindow.h>
#include <timerclock.h>
#include "armintcontrol.h"
struct buffer{
    volatile quint32 bufferIR;
    volatile bool isjump;
    volatile quint8 funx;
    volatile quint8 funy;
};
volatile static int msecond=0;
volatile static buffer data[3];
volatile quint8 index=0;

//static QSemaphore run1(0),run2(0),run3(0);
QSemaphore * thread0::run1=NULL;
QSemaphore * thread0::run2=NULL;
QSemaphore * thread0::run3=NULL;
//static QSemaphore wait1(0),wait2(0),wait3(0);
QSemaphore * thread0::wait1=NULL;
QSemaphore * thread0::wait2=NULL;
QSemaphore * thread0::wait3=NULL;
bool thread0::t0runflag=true;
bool thread1::runflag=true;
bool thread2::runflag=true;
bool thread3::runflag=true;
bool thread1::paused=false;
bool thread2::paused=false;
bool thread3::paused=false;
QFile * thread0::fnand=NULL;
extern quint32 R[16];
extern quint8 Member[1024*4];
extern  bool isjump;
#define PC R[15]
void (*cmd[8][18])(quint32 x)={NULL};
void fun(quint32 x){}
thread0::thread0(QObject * w):QThread(w){
    thread0::run1=new QSemaphore(0);
    thread0::run2=new QSemaphore(0);
    thread0::run3=new QSemaphore(0);
    thread0::wait1=new QSemaphore(0);
    thread0::wait2=new QSemaphore(0);
    thread0::wait3=new QSemaphore(0);
    data[0].isjump=false;
    data[1].isjump=true;
    data[2].isjump=true;
    index=0;
    PC=0;
    mypause=new QSemaphore(0);
    for(int i=0;i<8;i++){
        for(int j=0;j<18;j++){
            cmd[i][j]=fun;
        }
    }
    cmd[0][0]=bx;
    cmd[0][1]=and0;
    cmd[0][4]=add0;
    cmd[0][8]=tst0;
    cmd[0][10]=cmp;
    cmd[0][12]=orr0;
    cmd[0][13]=mov;
    cmd[0][14]=bic0;
    cmd[0][15]=mvn0;
    cmd[0][16]=mrs;
    cmd[0][17]=msr;
    cmd[1][0]=and1;
    cmd[1][4]=add1;
    cmd[1][8]=tst1;
    cmd[1][10]=cmp;
    cmd[1][12]=orr1;
    cmd[1][13]=movimm;
    cmd[1][14]=bic1;
    cmd[1][15]=mvn1;
    cmd[1][17]=msr_im;
    cmd[2][0]=ldr0;
    cmd[2][1]=str0;
    cmd[3][0]=ldr1;
    cmd[3][1]=str1;
    cmd[4][0]=LDM_STM;
    cmd[5][0]=b;
    cmd[7][15]=fun;

    this->fnand=new QFile("./flash/nand.flash");
    if(!(this->fnand->open(QIODevice::ReadWrite))){
     this->fnand=NULL;
    }
    t1=new thread1(w);
    t2=new thread2(w);
    t3=new thread3(w);
    //connect(t3,&thread3::mainwindowupdatas,w,&MainWindow::setR);
    t1->start();
    t2->start();
    t3->start();
}
void thread0::setspeed(int mmsecond){
    msecond=mmsecond;

}
thread1::thread1(QObject *w){}
void thread1::mstop(){thread1::runflag=false;}
bool thread1::ispaused(){return this->paused;}
thread2::thread2(QObject *w){}
void thread2::mstop(){thread2::runflag=false;}
bool thread2::ispaused(){return this->paused;}
bool thread0::ispaused(){return this->paused;}
void thread3::mstop(){thread3::runflag=false;}
bool thread3::ispaused(){return this->paused;}
thread3::thread3(QObject *w)
{
    this->w=(MainWindow *)w;

}
thread0::~thread0(){
    t0runflag=false;
    if(this->ispause()){this->unpause();}
    t3->mstop();
    t2->mstop();
    t1->mstop();
    t0runflag=false;
    //qDebug()<<"aaa";
    if(thread0::wait1!=NULL)thread0::wait1->release(2);
    if(thread0::wait2!=NULL)thread0::wait2->release(2);
    if(thread0::wait3!=NULL) thread0::wait3->release(2);
    if(thread0::run1!=NULL)thread0::run1->release(2);
    if(thread0::run2!=NULL)thread0::run2->release(2);
    if(thread0::run3!=NULL)thread0::run3->release(2);
    qDebug()<<"bbb";
    t1->quit();
    t1->wait(10);
    t2->quit();
    t2->wait(10);
    t3->quit();
    t3->wait(10);
    qDebug()<<"ccc";
    t0runflag=false;
    if(thread0::wait1!=NULL)thread0::wait1->release(2);
    if(thread0::wait2!=NULL)thread0::wait2->release(2);
    if(thread0::wait3!=NULL) thread0::wait3->release(2);
    if(thread0::run1!=NULL)thread0::run1->release(2);
    if(thread0::run2!=NULL)thread0::run2->release(2);
    if(thread0::run3!=NULL)thread0::run3->release(2);
    delete t1;
    delete t2;
    delete t3;
    //while(!this->ispaused());
    //quit();
    //wait(msecond);
    qDebug()<<"ddd";
    this->t0runflag=false;
    while (this->isRunning()) {

    }
   // this->quit();
   // this->wait(10);
    if(mypause!=NULL)delete mypause;
    if(thread0::run1!=NULL)delete thread0::run1;
    if(thread0::run2!=NULL)delete thread0::run2;
    if(thread0::run3!=NULL)delete thread0::run3;
    if(thread0::wait1!=NULL)delete thread0::wait1;
    if(thread0::wait2!=NULL)delete thread0::wait2;
    if(thread0::wait3!=NULL)delete thread0::wait3;
    mypause=NULL;
    thread0::run1=NULL;thread0::run2=NULL;thread0::run3=NULL;
    thread0::wait1=NULL;thread0::wait2=NULL;thread0::wait3=NULL;
    qDebug()<<"thread0 exit\n";
    if(this->fnand!=NULL&&this->fnand->isOpen()){
      this->fnand->close();
        this->fnand=NULL;
    }
}
thread1::~thread1(){
    runflag=false;
    /*if(thread0::run1!=NULL)
        thread0::run1->release(2);
    if(thread0::wait1!=NULL);
        thread0::wait1->release(2);*/
    //if(isRunning())quit();
     //wait();

    qDebug()<<"thread1 exit\n";
}
thread2:: ~thread2(){
    runflag=false;
    /*if(thread0::run2!=NULL)thread0::run2->release(2);
    if(thread0::wait2!=NULL)thread0::wait2->release(2);*/
    //quit();
    //wait();
    qDebug()<<"thread2 exit\n";
}
thread3::~thread3(){
    runflag=false;
    /*if(thread0::run3!=NULL)thread0::run3->release(2);
    if(thread0::wait3!=NULL)thread0::wait3->release(2);*/
    //quit();
    //wait();
    qDebug()<<"thread3 exit\n";
}
void views(quint32 n){
    QString str;
    for(int j=31;j>=0;j--){
        str+=QString("%1,").arg((n>>j)&1);
    }
    qDebug()<<str;
}
void thread0::pause(){
    if(!this->is_puase){
       this->is_puase=true;
    }
}
void thread0::unpause(){
    if(this->is_puaseed){
        mypause->release();
    }
}

bool thread0::ispause(){
    return this->is_puaseed;
}
bool thread0::isrun(){
    return this->t0runflag;
}
void thread0::run(){
    this->paused=false;
    t0runflag=true;
    reset();
    while(t0runflag){
         if(is_puase){
             is_puaseed=true;
             mypause->acquire();
             is_puase=false;
             is_puaseed=false;}
         thread0::wait1->release();
         thread0::wait2->release();
         thread0::wait3->release();
         this->msleep(msecond);
         thread0::run1->acquire();
         thread0::run2->acquire();
         thread0::run3->acquire();
         check();
         if(isjump){
             isjump=false;
             //qDebug()<<QString("jmp_________=%1\n").arg(PC,16);
             data[index%3].isjump=true;
             data[(index+2)%3].isjump=true;
         }
         else{
             PC+=4;
         }
         index++;
         index=index%3;
    }
    qDebug()<<"thread0 finished";
    this->paused=true;
}
void thread1::run(){
    this->paused=false;
    runflag=true;
    while(runflag){
        thread0::wait1->acquire();
        //printf("pc=%d\n",PC);
        //data[index%3].bufferIR=(Member[PC]<<24)+(Member[PC+1]<<16)+(Member[PC+2]<<8)+Member[PC+3];
        quint32 buffer;
        memcontrol(PC,true,buffer,4);
        data[index%3].bufferIR=buffer;
        //timerclock::exectimer();
        thread0::run1->release();
    }
    qDebug()<<"thread1 finished";
    this->paused=true;
}
void thread2::run(){
    this->paused=false;
    runflag=true;
    while(runflag){
        thread0::wait2->acquire();
        if(data[(index+2)%3].isjump){
            thread0::run2->release();
            continue;
        }
        qint8 codetype=(data[(index+2)%3].bufferIR>>25)&7;
        qint8 operation=(data[(index+2)%3].bufferIR>>21)&15;
        switch (codetype) {
        case 0:
            data[(index+2)%3].funx=0;
            //printf("duo zhiling register\n");

            if(0b0000==operation){
                //printf("and");
                data[(index+2)%3].funy=1;
                break;
            }
            if(0b0001==operation){

                //printf("eor");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b0010==operation){
                //printf("sub");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b0011==operation){
                //printf("rsb");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b0100==operation){
                //printf("add");
                data[(index+2)%3].funy=4;
                break;
            }
            if(0b0101==operation){
                //printf("adc");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b0110==operation){
                printf("sbc");data[(index+2)%3].funy=15;
                break;
            }
            if(0b0111==operation){
                //printf("rsc");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b1000==operation){
                if(((data[(index+2)%3].bufferIR&0b111111111111)==0)&&(((data[(index+2)%3].bufferIR>>16)&0b111111))==0b001111){
                    data[(index+2)%3].funy=16;
                     break;}// mrs
                data[(index+2)%3].funy=8;
                //printf("___tst0\n");
                break;
            }
            if(0b1001==operation){
                //printf("branch _bx\n");
                if(((data[(index+2)%3].bufferIR&0b111111110000)==0)&&(((data[(index+2)%3].bufferIR>>12)&0b1111111111))==0b1011111111){
                    data[(index+2)%3].funy=17;
                     break;}// msr
                if((((data[(index+2)%3].bufferIR>>4)&15)==1))
                data[(index+2)%3].funy=0;
            }
            if(0b1010==operation){
                //printf("cmp\n");
                if(((data[(index+2)%3].bufferIR&0b111111111111)==0)&&(((data[(index+2)%3].bufferIR>>16)&0b111111))==0b001111){
                    data[(index+2)%3].funy=16;
                     break;}// mrs
                //cmp();
                data[(index+2)%3].funy=10;
            }
            if(0b1011==operation){
                if(((data[(index+2)%3].bufferIR&0b111111110000)==0)&&(((data[(index+2)%3].bufferIR>>12)&0b1111111111))==0b1011111111){
                    data[(index+2)%3].funy=17;
                     break;}// msr
                //printf("cmn");
                data[(index+2)%3].funy=15;
                break;
            }
            if(0b1100==operation){
                //printf("orr");
                //orr();
                data[(index+2)%3].funy=12;
            }
            if(0b1101==operation){
                // mov();
                //printf("mov\n");
                data[(index+2)%3].funy=13;
            }
            if(0b1110==operation){
                //printf("bic\n");
                //bic();
                data[(index+2)%3].funy=14;
            }
            if(0b1111==operation){
                data[(index+2)%3].funy=15;
            }

            break;
        case 1:// 立即数
            data[(index+2)%3].funx=1;
           // printf("Data/processing/PSR Transfer\n");
            if(0b0000==operation){
                //printf("and");
                data[(index+2)%3].funy=0;
                break;
            }

            if(0b0010==operation){
                printf("sub \n");
            }
            if(0b0100==operation){
                //printf("add1");
                data[(index+2)%3].funy=4;
                break;
            }
            if(0b1000==operation){
                data[(index+2)%3].funy=8;
                break;
            }
            if(0b1010==operation){
                //printf("cmp\n");
                data[(index+2)%3].funy=10;//cmp();
                break;
            }
            if(0b1001==operation){
                //qDebug()<<"msr_im";
                if(((data[(index+2)%3].bufferIR>>12)&0b1111111111)==0b1011111111){
                    data[(index+2)%3].funy=17;
                     break;}
                data[(index+2)%3].funy=9;//
                break;
            }
            if(0b1011==operation){
                if(((data[(index+2)%3].bufferIR>>12)&0b1111111111)==0b1011111111){
                    data[(index+2)%3].funy=17;
                     break;}
                data[(index+2)%3].funy=11;//
                break;
            }
            if(0b1100==operation){
                //printf("orr\n");
                data[(index+2)%3].funy=12;//orr();
                break;
            }
            if(0b1101==operation){
                data[(index+2)%3].funy=13;
                break;
               // printf("li ji shu mov \n");
            }
            if(0b1110==operation){
                //printf("bic\n");
                data[(index+2)%3].funy=14;//bic();
                break;
            }
            if(0b1111==operation){
                data[(index+2)%3].funy=15;
            }
            break;
        case 2:
            data[(index+2)%3].funx=2;
            if(1==((data[(index+2)%3].bufferIR>>20)&1)){//load
             data[(index+2)%3].funy=0;
            }else{//ldr
             data[(index+2)%3].funy=1;
            }
            //qDebug()<<"STR/LDR Transfer LI JI SHUO\n";
            //LDR_STR();
            break;
        case 3:
            data[(index+2)%3].funx=3;
            if(1==((data[(index+2)%3].bufferIR>>20)&1)){//load
             data[(index+2)%3].funy=0;
            }else{//ldr
             data[(index+2)%3].funy=1;
            }
            //qDebug()<<"single Data Transfer STR/LDR Transfer JI CUN QI";
            //LDR_STR();
            break;
        case 4:
            //printf("block data Transfer\n");
            data[(index+2)%3].funx=4;
            data[(index+2)%3].funy=0;
            break;
        case 5:
            data[(index+2)%3].funx=5;
            data[(index+2)%3].funy=0;
            //printf("branch 5\n");
            //b();
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
        //printf("%d\n",codetype);
        thread0::run2->release();

    }
    qDebug()<<"thread2 finished";
    this->paused=true;
}
void thread3::run(){
    this->paused=false;
    runflag=true;
    while(runflag){
        thread0::wait3->acquire();
        if(data[(index+1)%3].isjump==false){
            QString str=QString("pc=%1").arg(QString::number(PC-8,16));
            //qDebug()<<str;
            if(msecond!=0)this->w->setpc(str);

            cmd[data[(index+1)%3].funx][data[(index+1)%3].funy](data[(index+1)%3].bufferIR);

            if((data[(index+1)%3].funx==2)||(data[(index+1)%3].funx==3)){
                this->w->update();
            }
            if(msecond!=0)this->w->setR();
            //views(data[(index+1)%3].bufferIR);
        }else{
            data[(index+1)%3].isjump=false;
        }
       thread0::run3->release();
    }
    qDebug()<<"thread3 finished";
    this->paused=true;
}
void thread0::check(){

}
void thread0::reset(){
    quint32 mask=0xffffffff;
    memcontrol((quint32)rINTMSK,false,mask,4);
    mask=0xffff;
    memcontrol((quint32)rINTSUBMSK,false,mask,4);
    mask=0xffffffff;
    memcontrol((quint32)rEINTMASK,false,mask,4);
}
