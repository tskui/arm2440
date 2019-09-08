#ifndef MEMBER_H
#define MEMBER_H

#include <QWidget>

namespace Ui {
class Member;
}

class Member : public QWidget
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = 0);
    ~Member();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Member *ui;
};

#endif // MEMBER_H
