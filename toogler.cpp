#include "toogler.h"
#include "stdio.h"


Toogler::Toogler(QObject *parent) :
    QThread(parent)
{
    m_enabled = false;
    m_period = 1000;
    m_high_period = 500;
    m_low_period = 500;
    m_dutyCycle = 50;
    pwmPin = new GPIO( 2 , 18 , GPIO::Out); //34_CN7
}

void
Toogler::vSetDutyCycle(int lDutyCycle)
{
    m_dutyCycle = lDutyCycle;
    m_high_period = m_period * m_dutyCycle/100;
    m_low_period = m_period - m_high_period;
    timer.start();
}

void
Toogler::vOnOff()
{
    m_enabled = !m_enabled;

    if(m_enabled)
    {
        m_state = GPIO::High;
        start();
    }
    else
    {
        m_state = GPIO::Low;
    }

    pwmPin->setState(m_state);
}

void
Toogler::vSetPeriod(int lPeriod)
{
    printf("New period = %d ms",lPeriod);
    m_period = lPeriod;
    m_high_period = m_period * m_dutyCycle/100;
    m_low_period = m_period - m_high_period;
    timer.restart();
    //timer.start();
}

void
Toogler::run()
{
    //static int counter = 0;
    timer.start();
    qint64 elapsed;

    while(m_enabled)
    {
        //counter++;
        //emit toogle();
        elapsed = timer.elapsed();

        if(m_state == GPIO::High)
        {
            if(elapsed >= m_high_period)
            {
                printf("Toogle to low after %lld\n",elapsed);
                m_state = GPIO::Low;
                pwmPin->setState(m_state);
                timer.start();
            }
        }
        else
        {
            if(elapsed >= m_low_period)
            {
                printf("Toogle to high after %lld\n",elapsed);
                m_state = GPIO::High;
                pwmPin->setState(m_state);
                timer.start();
            }
        }
    }
}
