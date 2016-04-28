#ifndef PWM_CTRL_H
#define PWM_CTRL_H

#include <QObject>

class PWM : public QObject
{
    Q_OBJECT

public:
    PWM();
    ~PWM();

    char getEnabled();

private:
    bool  m_enabled;
    int   m_dutyCycle;
    int   m_period;

public slots:
    void vSetDutyCycle(int);
    void vOnOff();
    void vSetPeriod(int);
};

#endif // PWM_CTRL_H
