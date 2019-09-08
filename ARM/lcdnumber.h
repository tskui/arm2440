#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QWidget>

class LCDNUMBER : public QWidget
{
    Q_OBJECT
public:
    bool ennable=false;
    explicit LCDNUMBER(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void clear();
signals:

public slots:

private:
    quint32 numdate;
};

#endif // LCDNUMBER_H
