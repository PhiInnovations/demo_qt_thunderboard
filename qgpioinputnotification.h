#ifndef QGPIOINPUTNOTIFICATION_H
#define QGPIOINPUTNOTIFICATION_H

#include <QObject>
#include <QSocketNotifier>
#include <qgpio.h>

class QGpioInputNotification : public QObject
{
    Q_OBJECT
public:
    QGpioInputNotification(int gpio_pin);
    ~QGpioInputNotification();
    int QGpioPinNumber();
    int keypad_fd(void);

private :
    QGpio  *this_gpio;
    QFile   gpio_value;
    QSocketNotifier *keypad_notifier;
    char current_value;
    int gpio_key;

signals:
    void button_pushed(QString value);

public slots:
     void ready_read(int);
};

#endif // QGPIOINPUTNOTIFICATION_H

