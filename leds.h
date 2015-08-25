#ifndef LEDS_H
#define LEDS_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QLabel>
#include "gpio_ctrl.h"

class Leds : public QWidget
{
    Q_OBJECT

public:
    Leds(QWidget *parent);

    int diameter() const { return m_diameter; }
    int numberOfLeds() const { return m_number; }
    int width() const { return m_width; }
    int height() const { return m_height; }

    void setDiameter(int diameter);
    void setLedNumber(int ledNb);
    void setWidth(int w);
    void setHeight(int h);

    static void setFakeGpios(const bool en) { Leds::m_fakeGpios = en;   }
    static bool fakeGpios()                 { return Leds::m_fakeGpios; }

//#ifdef GPIOS_DBG
protected:
    void mousePressEvent(QMouseEvent *event);
//#endif

protected slots:
    void paintEvent(QPaintEvent *event);

private slots:
    void toogleEvent(GPIO::PinState,GPIO*);

private:
    QPixmap generatePixmap(int);

    static bool     m_fakeGpios;

    QList<GPIO*>    leds;
    uchar           m_update;
    uchar           m_state;
    int             m_diameter;
    int             m_width;
    int             m_height;
    int             m_number;
};

#endif // LEDS_H
