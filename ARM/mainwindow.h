#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QResizeEvent>
#include <about.h>
#include <description.h>
#include <configpc.h>
#include <configio.h>
#include <member.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QLabel *lable,*lablepc;
    int timerid;
    About *about=NULL;
    Description *description=NULL;
    Configpc *configpc=NULL;
    Configio *cfgio=NULL;
    Member *member=NULL;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void winclose();
    void setpc(QString str);
    void resizeEvent(QResizeEvent* size);
    void closeEvent(QCloseEvent *e);
    void timerEvent(QTimerEvent *e);

public slots:


    void setR();
    void on_stop_clicked();

    void on_start_clicked();

    void on_xinpian2440_clicked();

    void on_pause_clicked();

    void on_speed_editingFinished();

    void on_speed_valueChanged(const QString &arg1);

    void on_KEY0_clicked();

    void on_KEY1_clicked();

    void on_KEY2_clicked();

    void on_KEY3_clicked();

    void openbin();

    void openhex();

    void openabout();

    void opendescription();

    void menuhovercolor();

    void openpc();

    void openio();

    void openmember();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
