#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QThread>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap pix(":/mysource/D:/Documents/Pictures/welcom.png");
    QPixmap pixs=pix.scaled(800,800, Qt::KeepAspectRatioByExpanding);
    QSplashScreen *splash=new QSplashScreen(pixs);
    splash->show();
    a.processEvents();
    splash->showMessage("LOVE11111111111111");
    QThread::sleep(5);
    w.show();
    splash->finish(&w);
    delete splash;
    return a.exec();
}
