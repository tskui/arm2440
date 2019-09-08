#ifndef CONFIGPC_H
#define CONFIGPC_H

#include <QDialog>
#include <beep.h>
#include <lamb.h>
namespace Ui {
class Configpc;
}

class Configpc : public QDialog
{
    Q_OBJECT

public:
    explicit Configpc(QWidget *parent = 0);
    int getpcnumber();
    void setpcnumber(int n);
    ~Configpc();

private:
    Ui::Configpc *ui;
};

#endif // CONFIGPC_H
