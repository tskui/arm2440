#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPixmap>
#include <QFileDialog>
#include <mytest.h>
#include <mythread.h>
#include <QLatin1Char>
#include <QDebug>
#include "lamb.h"
#include "FUNCMD.h"
#include <s3c2410.h>
#include <QMessageBox>
#include <windows.h>
#include <math.h>
#include <about.h>
#include <configpc.h>
typedef void (*waveopen)(LPHWAVEOUT phwo, UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen);
typedef void (*wavePrepareHeader)(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
typedef void (*waveWrite)(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
waveopen mywaveopen;
wavePrepareHeader myPrepareHeader;
waveWrite mywavewrite;

#define MUTE_LENGTH 500 //一秒采集完
#define SAMPLE_RATE 11025
#define HZ   300   //<=5500
#define T (1.0/HZ)
bool run = true;
extern quint32 R[16];
HWAVEOUT hwaveout;
char mute[MUTE_LENGTH];
WAVEFORMATEX waveformate;
WAVEHDR wavehdr;

void CALLBACK WaveCallback(HWAVEOUT hWave, UINT uMsg, DWORD dwUser,
    DWORD dw1, DWORD dw2)
{
    if (uMsg == WOM_DONE)
    {
       // printf("WOM_DONE、\n");
        //run = false;



    }
}
void beepinit(){
    HINSTANCE hdll;
    hdll = LoadLibrary(TEXT("testdll.dll"));
    if (hdll == NULL)
    {
        FreeLibrary(hdll);

    }
    else
    {
        mywaveopen = (waveopen)GetProcAddress(hdll, "mywaveOutOpen");
        myPrepareHeader=(wavePrepareHeader)GetProcAddress(hdll, "mywaveOutPrepareHeader");
        mywavewrite=(waveWrite)GetProcAddress(hdll, "mywaveOutWrite");
        if (mywaveopen == NULL||myPrepareHeader == NULL ||mywavewrite == NULL)
        {
           FreeLibrary(hdll);
        }else
        {
           qDebug()<<"dll init success";


           for (int i = 0; i < MUTE_LENGTH; i++)mute[i] = sin((2 * 3.14159) / T*i / SAMPLE_RATE) * 256;
           waveformate = {
               WAVE_FORMAT_PCM,
               1,
               SAMPLE_RATE,
               SAMPLE_RATE,
               1,8,0 };
           //waveformate.
           wavehdr = { 0,
                       MUTE_LENGTH,
                       0,0,0,1,
                       NULL,0 };
           //FillMemory(mute, MUTE_LENGTH, (BYTE)0x9c);
           wavehdr.lpData = mute;
           mywaveopen (&hwaveout, WAVE_MAPPER, &waveformate, (DWORD)WaveCallback, 0, CALLBACK_FUNCTION);
           myPrepareHeader(hwaveout, &wavehdr, sizeof(WAVEHDR));

        }
    }
}
extern quint32 R[16];
thread0 *t0;
//mytest* t;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("s3c2440虚拟实验平台设计"));
    this->setWindowIcon(QIcon(QPixmap(":/mysource/icon.png")));

    ui->start->setStyleSheet("QPushButton{border-image: url(:/mysource/start.png);}"
                  "QPushButton:hover{border-image: url(:/mysource/started.png);}"
                  "QPushButton:pressed{border-image: url(:/mysource/start.png);}");
    ui->pause->setStyleSheet("QPushButton{border-image: url(:/mysource/pause.png);}"
                  "QPushButton:hover{border-image: url(:/mysource/pauseed.png);}"
                  "QPushButton:pressed{border-image: url(:/mysource/pause.png);}");
    ui->stop->setStyleSheet("QPushButton{border-image: url(:/mysource/stop.png);}"
                  "QPushButton:hover{border-image: url(:/mysource/stoped.png);}"
                  "QPushButton:pressed{border-image: url(:/mysource/stop.png);}");
    ui->KEY0->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
    ui->KEY1->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
    ui->KEY2->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
    ui->KEY3->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
    //ui->beep->setStyleSheet("QLabel{border-image: url(:/mysource/keyup.png);}");
    ui->LCD_M->setStyleSheet("");
    lable=new QLabel(this);
    lablepc=new QLabel(this);
    ui->statusBar->addWidget(lable);
    ui->statusBar->addWidget(lablepc);
   // t=new mytest(this);
   // t->start();
   // timerid=this->startTimer(1000);
    newflash();
    t0=new thread0(this);

    connect(t0->t3,SIGNAL(mainwindowupdatas),this,SLOT(update));
    connect(ui->actionnand,SIGNAL(triggered()),this,SLOT(openbin()));
    connect(ui->actionnor,SIGNAL(triggered()),this,SLOT(openbin()));
    connect(ui->actionnand2,SIGNAL(triggered()),this,SLOT(openhex()));
    connect(ui->actionnor2,SIGNAL(triggered()),this,SLOT(openhex()));
    connect(ui->about,SIGNAL(triggered()),this,SLOT(openabout()));
    connect(ui->descption,SIGNAL(triggered()),this,SLOT(opendescription()));
    connect(ui->run,SIGNAL(triggered()),this,SLOT(on_start_clicked()));
    connect(ui->stop_2,SIGNAL(triggered()),this,SLOT(on_stop_clicked()));
    connect(ui->pause_2,SIGNAL(triggered()),this,SLOT(on_pause_clicked()));
    connect(ui->menu,SIGNAL(hovered()),this,SLOT(menuhovercolor()));
    connect(ui->actionPc,SIGNAL(triggered()),this,SLOT(openpc()));
    connect(ui->actionIo,SIGNAL(triggered()),this,SLOT(openio()));
    connect(ui->actionM,SIGNAL(triggered()),this,SLOT(openmember()));
    beepinit();
}
void MainWindow::setpc(QString str){
    this->lablepc->setText(str);
}
void MainWindow::closeEvent(QCloseEvent *e){
   qDebug()<<"QCloseEvent";
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openbin(){
    QString filename=QFileDialog::getOpenFileName(this,tr("打开烧写文件"),"C:\\Users\\Administrator\\Desktop\\a\\armtest\\",tr("all(*.bin)"));
    download(filename);
}
void MainWindow::openhex(){
    QString filename=QFileDialog::getOpenFileName(this,tr("打开烧写文件"),"C:\\Users\\Administrator\\Desktop\\a\\armtest\\",tr("all(*.hex)"));
    downloadhex(filename);
}
void MainWindow::openabout(){
    if(about==NULL){
        about=new About();}
    about->show();
}
void MainWindow::opendescription(){
    if(description==NULL){
        description=new Description();}
    description->show();
}
void MainWindow::openpc(){
    if(configpc==NULL){
        configpc=new Configpc();}
    int flag=configpc->exec();
    if(flag==QDialog::Accepted){
        R[15]= configpc->getpcnumber();
    }
    //qDebug()<<"hover\n"+QString::number(flag);
}
void MainWindow::openio(){
   if(cfgio==NULL){
      cfgio=new Configio();
       }
     cfgio->checkstate(ui->BEEPS,ui->widget,ui->widget_2,ui->LCD_M);
     int flag=cfgio->exec();

     if(flag==QDialog::Accepted){
         qDebug()<<"hover\n"+QString::number(flag);
         cfgio->cfgbeep(ui->BEEPS);\
         cfgio->cfgled(ui->widget);
         cfgio->cfgLCDNUMBER(ui->widget_2);
         cfgio->cfgLCD(ui->LCD_M);
         this->update();
     }

}
void MainWindow::openmember(){
    if(member==NULL){
        member=new Member();
    }
    member->show();
}
void MainWindow::menuhovercolor(){
    qDebug()<<"hover\n";
}
void MainWindow::on_pause_clicked()
{
    if(t0!=NULL&&t0->isRunning()){
        if(t0->ispause()){
            t0->unpause();
            ui->pause->setText("暂停");
            lable->setText("run!");
        }
        else{
            t0->pause();
            ui->pause->setText("运行");
            lable->setText("pause run!");
        }
        qDebug()<<"on_pause_clicked\n";
    }
}
void MainWindow::on_stop_clicked()
{
    if(t0!=NULL&&t0->isRunning()){
        delete t0;
        t0=NULL;
        ui->pause->setText("暂停");
        lable->setText("stop run!");
        qDebug()<<"t0!=NULL&&t0->isRunning() stop t0\n";
    }
    else{
        lable->setText("stoped run!");
        qDebug()<<"on_stop_clicked\n";
    }
}

void MainWindow::on_start_clicked()
{
    if(t0!=NULL&&t0->isRunning()){
        qDebug()<<"thread is not null or running\n";
        lable->setText("runing!");
        return;
    }
    else{
        loadcode();
        t0=new thread0(this);
        lable->setText("runing!");
        qDebug()<<"thread run start\n";
        t0->start();
    }
}

void MainWindow::on_xinpian2440_clicked()
{   QMessageBox customMsgBox;
    customMsgBox.setWindowTitle( tr( "烧写文件类型" ) );
    customMsgBox.setText(tr("请选择烧写文件类型"));

    QPushButton * bin = customMsgBox.addButton( tr( "BIN" ), QMessageBox::ActionRole );
    QPushButton * hex = customMsgBox.addButton( tr( "HEX" ), QMessageBox::ActionRole );
    QPushButton * cancelButton = customMsgBox.addButton( QMessageBox::Cancel );
    customMsgBox.exec();
    if ( customMsgBox.clickedButton() == bin ){
        QString filename=QFileDialog::getOpenFileName(this,tr("打开烧写文件"),"C:\\Users\\Administrator\\Desktop\\a\\armtest\\",tr("all(*.bin)"));
        download(filename);
    }
    if ( customMsgBox.clickedButton()== hex ){
        QString filename=QFileDialog::getOpenFileName(this,tr("打开烧写文件"),"C:\\Users\\Administrator\\Desktop\\a\\armtest\\",tr("all(*.hex)"));
        downloadhex(filename);
    }
    if ( customMsgBox.clickedButton() == cancelButton ){

    }
    qDebug()<<"on_xinpian2440_clicked\n";
}


void MainWindow::on_speed_editingFinished()
{
    if(t0!=NULL)t0->setspeed(ui->speed->value());
}

void MainWindow::on_speed_valueChanged(const QString &arg1)
{
    if(t0!=NULL)t0->setspeed(ui->speed->value());
}
void MainWindow::resizeEvent(QResizeEvent* size){
    int width=ui->frame_2->width();
    int height=ui->frame_2->height();
    ui->xinpian2440->setGeometry(width*0.42,height*0.48,width*0.15,height*0.23);
    ui->widget->setGeometry(width*0.15,height*0.3,40,160);
    ui->widget_2->setGeometry(width*0.2,height*0.25,200,70);

    ui->BEEPS->setGeometry(width*0.76,height*0.4,100,100);
    ui->LCD_M->setGeometry(width*0.54,height*0.1,200,300);
}
void MainWindow::timerEvent(QTimerEvent *e){
    qDebug()<<"timer kaishi ";
   // this->killTimer(timerid);
}
void MainWindow::setR(){
    ui->r0->setText("0X"+QString::number(R[0],16));
    ui->r1->setText("0X"+QString::number(R[1],16));
    ui->r2->setText("0X"+QString::number(R[2],16));
    ui->r3->setText("0X"+QString::number(R[3],16));
    ui->r4->setText("0X"+QString::number(R[4],16));
    ui->r5->setText("0X"+QString::number(R[5],16));
    ui->r6->setText("0X"+QString::number(R[6],16));
    ui->r7->setText("0X"+QString::number(R[7],16));
    ui->r8->setText("0X"+QString::number(R[8],16));
    ui->r9->setText("0X"+QString::number(R[9],16));
    ui->r10->setText("0X"+QString::number(R[10],16));
    ui->r11->setText("0X"+QString::number(R[11],16));
    ui->r12->setText("0X"+QString::number(R[12],16));
    ui->r13->setText("0X"+QString::number(R[13],16));
    ui->r14->setText("0X"+QString::number(R[14],16));
    ui->r15->setText("0X"+QString::number(R[15],16));
}
void MainWindow::on_KEY0_clicked()
{   static bool keyup=true;//GPF4
    quint32 keyvalue=0;
    memcontrol(rGPFDAT,true,keyvalue,4);
    if(keyup){
        keyvalue=keyvalue&0XFFFFFFEF;
        memcontrol(rGPFDAT,false,keyvalue,4);
        ui->KEY0->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
        keyup=false;
    }
    else{
        keyvalue=keyvalue|0B00010000;
        memcontrol(rGPFDAT,false,keyvalue,4);
        ui->KEY0->setStyleSheet("QPushButton{border-image: url(:/mysource/keydown.png);}");
        keyup=true;
    }
}

void MainWindow::on_KEY1_clicked()
{
    static bool keyup=true;
    quint32 keyvalue=0;
    memcontrol(rGPFDAT,true,keyvalue,4);
        if(keyup){
            keyvalue=keyvalue&0XFFFFFFDF;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY1->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
            keyup=false;
        }
        else{
            keyvalue=keyvalue|0B00100000;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY1->setStyleSheet("QPushButton{border-image: url(:/mysource/keydown.png);}");
            keyup=true;
        }
}

void MainWindow::on_KEY2_clicked()
{
    static bool keyup=true;
    quint32 keyvalue=0;
    memcontrol(rGPFDAT,true,keyvalue,4);
        if(keyup){
            keyvalue=keyvalue&0XFFFFFFBF;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY2->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
            keyup=false;
        }
        else{
            keyvalue=keyvalue|0B01000000;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY2->setStyleSheet("QPushButton{border-image: url(:/mysource/keydown.png);}");
            keyup=true;
        }
}

void MainWindow::on_KEY3_clicked()
{
    static bool keyup=true;
    quint32 keyvalue=0;
    memcontrol(rGPFDAT,true,keyvalue,4);
        if(keyup){
            keyvalue=keyvalue&0XFFFFFF7F;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY3->setStyleSheet("QPushButton{border-image: url(:/mysource/keyup.png);}");
            keyup=false;
        }
        else{
            keyvalue=keyvalue|0B10000000;
            memcontrol(rGPFDAT,false,keyvalue,4);
            ui->KEY3->setStyleSheet("QPushButton{border-image: url(:/mysource/keydown.png);}");
            keyup=true;
        }
}
