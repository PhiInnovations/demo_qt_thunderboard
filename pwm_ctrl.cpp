#include <QDir>
#include <QTextStream>
#include <QDebug>
#include "pwm_ctrl.h"


PWM::PWM()
{ 
    m_enabled = false;

    FILE * fp;

    if ((fp = fopen("/sys/class/pwm/pwmchip0/export", "ab")) != NULL)
    {
        rewind(fp); // aponta para o inicio do arquivo
        fputc('2', fp);
        fclose(fp);
    }

    if(getEnabled()=='1')
    {
        m_enabled = true;
    }

    // 1us e 50% duty cycle
    m_dutyCycle = 50;
    vSetPeriod(1000);
    //vSetDutyCycle(50);
}

char PWM::getEnabled()
{
    FILE * fp;
    char text = '0';
    if ((fp = fopen("/sys/class/pwm/pwmchip0/pwm2/enable", "rb+")) != NULL)
    {

        rewind(fp);//Set pointer to begining of the file
        fread(&text, 1 * sizeof(char),1, fp);
        fclose(fp);
    }

    return text;

}

PWM::~PWM(){

}

/**
 * @brief PWM::vSetDutyCycle
 * @param lDutyCycle            duty cycle em porcentagem
 */
void
PWM::vSetDutyCycle(int lDutyCycle)
{
    FILE * fp;

    m_dutyCycle = lDutyCycle;

    if ((fp = fopen("/sys/class/pwm/pwmchip0/pwm2/duty_cycle", "rb+")) != NULL)
    {

        rewind(fp); // aponta para o inicio do arquivo

        QString duty_str = QString::number((int)((lDutyCycle/100.0)*m_period));

        //qDebug() << "duty " << duty_str;

        fwrite(duty_str.toLatin1(), sizeof(char),duty_str.length(), fp);

        fclose(fp);
    }
}

void
PWM::vOnOff()
{
    m_enabled = !m_enabled;

    FILE * fp;

    if ((fp = fopen("/sys/class/pwm/pwmchip0/pwm2/enable", "rb+")) != NULL)
    {

        rewind(fp); // aponta para o inicio do arquivo

        fputc(m_enabled ? '1' : '0' ,fp);
        fclose(fp);
    }
}

/**
 * @brief PWM::vSetPeriod
 * @param lPeriod           periodo em ns
 */
void
PWM::vSetPeriod(int lPeriod)
{
    m_period = lPeriod;

    FILE * fp;

    if ((fp = fopen("/sys/class/pwm/pwmchip0/pwm2/period", "rb+")) != NULL)
    {

        rewind(fp); // aponta para o inicio do arquivo

        QString period_str = QString::number(lPeriod);

        //qDebug() << "period " << period_str;

        fwrite(period_str.toLatin1(), sizeof(char),period_str.length(), fp);

        fclose(fp);
    }

    vSetDutyCycle(m_dutyCycle);
}
