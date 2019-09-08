#ifndef BEEPTHREAD_H
#define BEEPTHREAD_H
#include <QThread>
#include <windows.h>
#include <QSemaphore>

#define MUTE_LENGTH 11025*2 //一秒采集完
#define SAMPLE_RATE 11025

class BeepThread : public QThread
{
    Q_OBJECT
public:
    QSemaphore *sembeep=new QSemaphore(0);
    /*static HWAVEOUT hwaveout;
    static char mute[MUTE_LENGTH];
    static WAVEFORMATEX waveformate;
    static WAVEHDR wavehdr;*/

    bool flag=true;
    bool beepstart=false;
    explicit BeepThread();
    void run();
    void stopBeep();
    void startBeep();
signals:

public slots:

};

#endif // BEEPTHREAD_H
