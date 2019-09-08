#include "beepthread.h"
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#pragma comment(lib,"winmm.lib")
typedef void (*waveopen)(LPHWAVEOUT phwo, UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen);
typedef void (*wavePrepareHeader)(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
typedef void (*waveWrite)(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
extern waveopen mywaveopen;
extern wavePrepareHeader myPrepareHeader;
extern waveWrite mywavewrite;
#define HZ   300
#define T (1.0/HZ)
/*void CALLBACK WaveCallback(HWAVEOUT hWave, UINT uMsg, DWORD dwUser,
    DWORD dw1, DWORD dw2)
{
    if (uMsg == WOM_DONE)
    {
        printf("WOM_DONE、\n");
        //run = false;
    }
}*/
extern HWAVEOUT hwaveout;
extern WAVEFORMATEX waveformate;
extern WAVEHDR wavehdr;
BeepThread::BeepThread() :QThread()
{

    /*for (int i = 0; i < MUTE_LENGTH; i++)mute[i] = sin((2 * 3.14159) / T*i / SAMPLE_RATE) * 256;
    waveformate = {
        WAVE_FORMAT_PCM,
        1,
        SAMPLE_RATE,
        SAMPLE_RATE,
        1,8,0 };
    //waveformate.
    wavehdr = { 0,MUTE_LENGTH,0,0,0,1,NULL,0 };
    //FillMemory(mute, MUTE_LENGTH, (BYTE)0x9c);
    wavehdr.lpData = mute;
    mywaveopen (&hwaveout, WAVE_MAPPER, &waveformate, (DWORD)WaveCallback, 0, CALLBACK_FUNCTION);
    myPrepareHeader(hwaveout, &wavehdr, sizeof(WAVEHDR));*/

}
void BeepThread::run(){

    while (flag) {
            sembeep->acquire();
            mywavewrite(hwaveout, &wavehdr, sizeof(WAVEHDR));
            sembeep->release();
    }

}
void BeepThread::stopBeep(){
    if(beepstart==true){
        beepstart=false;
        sembeep->acquire();
    }

}
void BeepThread::startBeep(){
    if(beepstart==false){
        beepstart=true;
        sembeep->release();
    }
}
