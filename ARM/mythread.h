#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>
#include <FUNCMD.h>
#include <QWidget>
#include <mainwindow.h>
#include <QObject>
#include <QFile>
class thread1:public QThread{
  static bool runflag;
  static bool paused;
   quint32 i=0;
   public:

    thread1(QObject *w);
    ~thread1();
    void mstop();
    bool ispaused();
   protected:
    void run();

};
class thread2:public QThread{
   static bool runflag;
   static bool paused;
    quint32 i=0;
    public:
       thread2(QObject *w);
       ~thread2();
       void mstop();
       bool ispaused();
   protected:
    void run();
};
class thread3:public QThread{
     static bool runflag;
     static bool paused;
     MainWindow *w;
     quint32 i=0;


public:
        thread3(QObject *w);
        ~thread3();
        void mstop();
        bool ispaused();

signals:
        void mainwindowupdatas();

protected:
    void run();

};
class thread0:public QThread{
   static bool t0runflag;
   bool is_puase=false;
   bool is_puaseed=false;
   bool paused=false;
   QSemaphore *mypause;
   quint32 i=0;
   public:
   static QFile * fnand;
   static QSemaphore  *run1,*run2,*run3;
   static QSemaphore *wait1,*wait2,*wait3;
   thread1* t1;
   thread2* t2;
   thread3* t3;
    thread0(QObject *w);
    ~thread0();
    void pause();
    void unpause();
    bool ispause();
    bool isrun();
    void setspeed(int msecond);

    bool ispaused();
    void check();
    void reset();

   protected:
    void run();
};

#endif // MYTHREAD_H
