#ifndef FUNCMD_H
#define FUNCMD_H
#include <QCoreApplication>
void newflash();
quint32 loadcode();
quint32 download(QString namefile);
void downloadhex(QString namefile);
void b(quint32 IR);
void bx(quint32 IR);
void bl(quint32 IR);
void blx(quint32 IR);
void mov(quint32 IR);
void bic0(quint32 IR);
void bic1(quint32 IR);
void orr(quint32 IR);
void cmp(quint32 IR);
void LDR_STR(quint32 IR);
void movimm(quint32 IR);
void and0(quint32 IR);
void and1(quint32 IR);
void sub0(quint32 IR);
void sub1(quint32 IR);
void add0(quint32 IR);
void add1(quint32 IR);
void orr0(quint32 IR);
void orr1(quint32 IR);
void LDM_STM(quint32 IR);
void msr(quint32 IR);
void msr_im(quint32 IR);
void mrs(quint32 IR);
void tst0(quint32 IR);
void tst1(quint32 IR);
void mvn0(quint32 IR);
void mvn1(quint32 IR);
void str0(quint32 IR);
void str1(quint32 IR);
void ldr0(quint32 IR);
void ldr1(quint32 IR);
#endif // FUNCMD_H
