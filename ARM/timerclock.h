#ifndef TIMERCLOCK_H
#define TIMERCLOCK_H
#include <QCoreApplication>
#include "s3c2410.h"
class timerclock
{
public:
    timerclock();
    static quint16 TCMPB0,TCMPB1,TCMPB2,TCMPB3;//4没有输出
    static quint16 TCNTB0,TCNTB1,TCNTB2,TCNTB3,TCNTB4;
    static bool startflag0,startflag1,startflag2,startflag3,startflag4;
    static void timer();
    static void exectimer();

};

#endif // TIMERCLOCK_H
