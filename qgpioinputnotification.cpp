#include "qgpioinputnotification.h"
#include <QDebug>

QGpioInputNotification::QGpioInputNotification(int gpio_pin) {
    this_gpio = new QGpio(gpio_pin);
    gpio_key = gpio_pin;
    if (!this_gpio) {
        abort();
    } else {
        QString gpio_value_path;
        gpio_value_path = QString::fromStdString(this_gpio->gpio_get_path());
        qDebug() << "keypad path=" << gpio_value_path;
        gpio_value.setFileName(gpio_value_path);      /* Set up the value file */
        this_gpio->gpio_set_direction("in");
        this_gpio->gpio_set_edge("both");               /* Interrupt on rising edge */
        gpio_value.open(QFile::ReadOnly);
        keypad_notifier = new QSocketNotifier(gpio_value.handle(), QSocketNotifier::Exception);
        keypad_notifier->setEnabled(true);
        connect(keypad_notifier, SIGNAL(activated(int)), this, SLOT(ready_read(int)));
    } /* endif */

}

QGpioInputNotification::~QGpioInputNotification() {
    gpio_value.close();
    this_gpio->gpio_set_edge("none");             /* Don't generate interrupts. */
    delete keypad_notifier;
    delete this_gpio;
}

int QGpioInputNotification::keypad_fd(void) {
    return gpio_value.handle();
} /* keypad_fd */


int QGpioInputNotification::QGpioPinNumber() {
    return gpio_key;
}

void QGpioInputNotification::ready_read(int) {
    QByteArray line;
    gpio_value.seek(0);
    char last_value = current_value;
    line = gpio_value.readAll();

    if (line.size() < 1) {
        abort();
    } else {
        current_value = line[0];
        emit button_pushed(QChar(current_value));
        qDebug() << "click" << current_value;
    } /* endif */
    if (current_value != last_value) {
                // qDebug() << "switch value changed, old=" << last_value << "current_value" << current_value;
    } /* endif */
}

