#ifndef MYTEST_H
#define MYTEST_H
#include <QObject>
#include <QThread>
#include <QWidget>
#include <mainwindow.h>
class mytest:public QThread
{   MainWindow *w;
    bool isrun=true;
public:
    mytest(QObject *ww);
    ~mytest();
protected:
    void run();
};

#endif // MYTEST_H
