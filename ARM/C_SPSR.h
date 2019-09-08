#ifndef C_SPSR_H
#define C_SPSR_H
#include <QCoreApplication>
#ifndef CPSR
extern quint32 CPSR;//程序状态寄存器N Z C V Q DNM(RAZ) I F T M4 M3 M2 M1 M0
extern quint32 SPSR_FIQ;//程序状态保存寄存器
extern quint32 SPSR_IRQ;//程序状态保存寄存器
extern quint32 SPSR_SUPERVISOR;//程序状态保存寄存器
extern quint32 SPSR_ABORT;//程序状态保存寄存器
extern quint32 SPSR_UNDEFINEED;//程序状态保存寄存器
#define SET_CPSR_N_0 CPSR=CPSR&0X7FFFFFFF
#define SET_CPSR_N_1 CPSR=CPSR|0X80000000

#define SET_CPSR_Z_0 CPSR=CPSR&0XBFFFFFFF
#define SET_CPSR_Z_1 CPSR=CPSR|0X40000000

#define SET_CPSR_C_0 CPSR=CPSR&0XDFFFFFFF
#define SET_CPSR_C_1 CPSR=CPSR|0X20000000

#define SET_CPSR_V_0 CPSR=CPSR&0XEFFFFFFF
#define SET_CPSR_V_1 CPSR=CPSR|0X10000000
#endif
#endif // C_SPSR_H
