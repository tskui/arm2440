#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QWidget>

namespace Ui {
class Description;
}

class Description : public QWidget
{
    Q_OBJECT

public:
    explicit Description(QWidget *parent = 0);
    ~Description();

private:
    Ui::Description *ui;
};

#endif // DESCRIPTION_H
