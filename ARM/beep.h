#ifndef BEEP_H
#define BEEP_H

#include <QWidget>
#include "beepthread.h"
class BEEP : public QWidget
{
    Q_OBJECT
public:
    bool ennable=false;
    BeepThread *t=new BeepThread();
    explicit BEEP(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // BEEP_H
