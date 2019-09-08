#ifndef LAMB_H
#define LAMB_H

#include <QWidget>
class lamb : public QWidget
{
    Q_OBJECT
public:
    bool ennable=true;
    explicit lamb(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // LAMB_H
