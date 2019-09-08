#ifndef DATA_H
#define DATA_H
#include <QCoreApplication>
#define LSL 0B00
#define LSR 0B01
#define ASL 0B10
#define ROR 0B11 //ROTATE RIGHT
extern quint32 IR;
extern quint32 CYC_BUFFER;
#ifndef cyc_right(_n_)
#define cyc_right(_n_) CYC_BUFFER=(IR&255);\
    CYC_BUFFER=CYC_BUFFER<<(32-_n_-_n_);\
    CYC_BUFFER=CYC_BUFFER|((IR&255)>>(_n_+_n_));\

#endif
#endif // DATA_H
