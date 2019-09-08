#ifndef LCD_H
#define LCD_H

#include <QWidget>

namespace Ui {
class LCD;
}

class LCD : public QWidget
{
    Q_OBJECT

public:
    char str[9][10]={{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    bool ennable=false;
    explicit LCD(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~LCD();

private:
    Ui::LCD *ui;
};

#endif // LCD_H
