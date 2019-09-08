#ifndef CONFIGIO_H
#define CONFIGIO_H

#include <QDialog>
#include <beep.h>
#include <lamb.h>
#include <lcdnumber.h>
#include <lcd.h>
namespace Ui {
class Configio;
}

class Configio : public QDialog
{
    Q_OBJECT

public:
    explicit Configio(QWidget *parent = 0);
    void cfgbeep(BEEP *beep);
    void cfgled(lamb *lamb);
    void cfgLCDNUMBER(LCDNUMBER *lcdnumber);
    void cfgLCD(LCD *lcd);
    void checkstate(BEEP *beep,lamb *lamb,LCDNUMBER *lcdnumber,LCD *lcd);
    ~Configio();

private:
    Ui::Configio *ui;
};

#endif // CONFIGIO_H
