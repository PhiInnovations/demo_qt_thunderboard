#ifndef GPIO_CTRL_H
#define GPIO_CTRL_H

#include <QObject>
#include <QSocketNotifier>
#include <QFile>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

class GPIO : public QObject
{
    Q_OBJECT
public:
    enum PinDirection {In,Out,Err};
    enum PinState     {Low, High};

    explicit GPIO(int gpioPort, int gpioPin, PinDirection direction, PinState initialState = Low , bool hasGpio0 = true);
    ~GPIO();

    int openPin();
    int closePin();

    void monitorPinValue(bool active);

    int setDirection(PinDirection direction);   //set direction in/out - returns 0 if ok and -1 on error
    PinDirection getDirection();                //returns direction
    int setState(PinState state);
    PinState getState();
    int gpio_set_edge(const char * edge_name);

    int pinNumber() const { return _pinNumber; }

public slots:
    void toogle();
       
private:
    int           _pinNumber;
    QFile         gpio_value;

    QSocketNotifier * pinMonitor;

private slots:
    void notifyToogle(int);

signals:
    void sgChanged(GPIO::PinState,GPIO* sender);//PinState currentState);
};
#endif // GPIO_CTRL_H
