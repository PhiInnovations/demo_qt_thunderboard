#ifndef TOOGLER_H
#define TOOGLER_H

#include <QThread>
#include <QElapsedTimer>
#include "gpio_ctrl.h"

class Toogler : public QThread
{
    Q_OBJECT
public:
    explicit Toogler(QObject *parent = 0);

    void run();

private:
    GPIO * pwmPin;

    QElapsedTimer timer;

    int   m_dutyCycle;
    int   m_period;
    bool  m_enabled;
    int   m_high_period;
    int   m_low_period;
    GPIO::PinState m_state;

signals:
    void toogle();

public slots:
    void vSetDutyCycle(int);
    void vOnOff();
    void vSetPeriod(int);

};

#endif // TOOGLER_H
