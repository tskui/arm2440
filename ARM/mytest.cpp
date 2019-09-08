#include "mytest.h"

mytest::mytest(QObject *ww):QThread(ww)
{
    this->w=(MainWindow *)ww;
}
void mytest::run(){
   while(isrun)
   {
    w->update();
    sleep(1);}
}
mytest::~mytest(){
    isrun=false;
}
