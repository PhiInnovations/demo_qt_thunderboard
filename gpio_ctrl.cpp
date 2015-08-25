#include <QDir>
#include <QTextStream>
#include "gpio_ctrl.h"

GPIO::GPIO(int gpioPort, int gpioPin, PinDirection direction, PinState initialState, bool hasGpio0) :
    _pinNumber      ( ( hasGpio0 ?  gpioPort : (gpioPort - 1) ) * 32 + gpioPin )
{
    openPin();
    setDirection(direction);
    gpio_value.setFileName(QString("/sys/class/gpio/gpio%1/value").arg(_pinNumber));

    if(direction == Out)
    {
       setState(initialState) ;
    }
    else
    {
        gpio_set_edge("both");               /* Interrupt on rising edge */
        monitorPinValue(true);
    }
}

GPIO::~GPIO()
{
    closePin();
}

int GPIO::openPin()
{
    FILE * fp;

    if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
        return -1;

    QString _strPin = QString("%1").arg(_pinNumber);

    rewind(fp); // aponta para o inicio do arquivo
    fwrite(_strPin.toLatin1(), sizeof(char),_strPin.length() , fp);
    fclose(fp);

    return 0;
}

void GPIO::monitorPinValue(bool active)
{
    if(active)
    {
        //inicia o monitoramento
        gpio_value.open(QFile::ReadOnly);
        if(gpio_value.handle() >= 0)
        {
            pinMonitor= new QSocketNotifier(gpio_value.handle(),QSocketNotifier::Exception,this);
            QObject::connect(pinMonitor,SIGNAL(activated(int)),this,SLOT(notifyToogle(int)));
        }

    }
    else
    {
        gpio_value.close();
        QObject::disconnect(pinMonitor,SIGNAL(activated(int)),this,SIGNAL(notifyToogle(int)));
        pinMonitor->~QSocketNotifier();

    }
}

void GPIO::notifyToogle(int){
    //printf("%d toogled\n",_pinNumber);
    QByteArray line;
    gpio_value.seek(0);
    //char last_value = current_value;
    line = gpio_value.readAll();

    if (line.size() >= 1) {
//         abort();
//    } else {
        char current_value = line[0];
        emit sgChanged((GPIO::PinState) (current_value - 48),this);
        //qDebug() << "click" << current_value;
    } /* endif */
}

void GPIO::toogle(){

    if(getState() == Low)
    {
        setState(High);
    }
    else
    {
        setState(Low);
    }
}

int GPIO::closePin()
{
	FILE * fp;

    if ((fp = fopen("/sys/class/gpio/unexport", "ab")) == NULL)
        return -1;

    QString _strPin = QString("%1").arg(_pinNumber);

    rewind(fp); // aponta para o inicio do arquivo
    fwrite(_strPin.toLatin1(), sizeof(char),_strPin.length() ,fp);
    fclose(fp);

    return 0;

}


int GPIO::setDirection(PinDirection direction)
{ 
    FILE * fp;

    if ((fp = fopen(QString("/sys/class/gpio/gpio%1/direction").arg(_pinNumber).toLatin1(), "rb+")) == NULL)
		return -1;

    rewind(fp); // aponta para o inicio do arquivo

    if(direction == In)
        fwrite("in", sizeof(char), 2, fp);
    if(direction == Out)
        fwrite("out", sizeof(char),3, fp);

    fclose(fp);
    return 0;
}

GPIO::PinDirection GPIO::getDirection()
{
    FILE * fp;
    char text[3];
    if ((fp = fopen(QString("/sys/class/gpio/gpio%1/direction").arg(_pinNumber).toLatin1(), "rb+")) == NULL){
        return Err;
    }

    rewind(fp);//Set pointer to begining of the file
    fread(text, 3 * sizeof(char),1, fp);
    fclose(fp);

    if(strcmp(text,"out"))
        return Out;
    else if(strcmp(text,"in"))
        return In;

    return Err;

}

int GPIO::gpio_set_edge(const char *edge_name) {
    int rc=-1;

    QDir gpio_directory = QDir("/sys/class/gpio/gpio" + QString::number(_pinNumber) + "/");
    QFile edge_file(gpio_directory.path() + "/edge");
    if (!edge_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_edge(&edge_file);
        out_edge << QString::fromStdString(edge_name);
        edge_file.close();
        rc = 1;
    } /* endif */
    return rc;
}

int GPIO::setState(PinState state)
{
    FILE * fp;
    if ((fp = fopen(QString("/sys/class/gpio/gpio%1/value").arg(_pinNumber) .toLatin1(), "rb+")) == NULL)
    	return -1;

    rewind(fp); // aponta para o inicio do arquivo

    if(state == High)
        fwrite("1", sizeof(char),1, fp);
    else
        fwrite("0", sizeof(char),1, fp);

    fclose(fp);
    return 0;
}

//returns 1 or 0 - the pin state. Returns -1 on error
GPIO::PinState GPIO::getState()
{
	FILE * fp;
    char value;
    if ((fp = fopen(QString("/sys/class/gpio/gpio%1/value").arg(_pinNumber).toLatin1(), "rb+")) == NULL){
        return Low;
    }

	rewind(fp);//Set pointer to begining of the file
	fread(&value, sizeof(char),1, fp);
    fclose(fp);

    if(value=='1') return High;

    return Low;
}
