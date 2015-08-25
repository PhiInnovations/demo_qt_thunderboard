#include <QPixmapCache>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include "leds.h"

bool Leds::m_fakeGpios = atoi(qgetenv("FAKE_GPIOS")) ? true : false;

Leds::Leds(QWidget *parent)
    : QWidget(parent),
      m_diameter(50),  m_number(4), m_width(75), m_height(360)
{
    leds.append(new GPIO( 0 , 22 , GPIO::In)); //52_CN7
    leds.append(new GPIO( 0 , 18 , GPIO::In)); //53_CN7
    leds.append(new GPIO( 0 , 23 , GPIO::In)); //54_CN7
    leds.append(new GPIO( 0 , 19 , GPIO::In)); //55_CN7

    QLabel * lbl;

    for( int i = 0 ; i < m_number ;  i++)
    {
        lbl = new  QLabel(tr("Switch").append(QString(" %1").arg(i+1)),this);
        lbl->setFont(QFont("Ubuntu",16));
        lbl->setGeometry(m_width + m_diameter,( i * m_height) / m_number, 3 * m_width , m_height / m_number);

        connect(leds.at(i),SIGNAL(sgChanged(GPIO::PinState,GPIO*)),
                this,SLOT(toogleEvent(GPIO::PinState,GPIO*)),
                Qt::UniqueConnection);
    }

}

QPixmap Leds::generatePixmap(int ledOn)
{
    QPixmap pixmap(m_width, m_height / m_number);
    QPainter painter(&pixmap);

    painter.setBrush(QColor(187,254,245));
    painter.setPen(QColor(187,254,245));
    painter.drawRect(0, 0, m_width, m_height / m_number);

    painter.setBrush(ledOn ? Qt::darkGreen : Qt::lightGray);
    painter.drawEllipse( (m_width - m_diameter) / 2,
                         ( (m_height / m_number) - m_diameter) / 2 ,
                         m_diameter,
                         m_diameter);

    return pixmap;
}

void Leds::setDiameter(int diameter)
{
    m_diameter = diameter;
    update();
    updateGeometry();
}


void Leds::setLedNumber(int ledNb)
{
    m_number = ledNb;
    update();
    updateGeometry();
}


void Leds::setWidth(int w)
{
    m_width = w;
    update();
    updateGeometry();
}

void  Leds::setHeight(int h)
{
    m_height = h;
    update();
    updateGeometry();
}

//#ifdef GPIOS_DBG
void Leds::mousePressEvent(QMouseEvent *event)
{
    if(Leds::m_fakeGpios){
        int dy = m_height / m_number;
        if (event->y() < dy) {
            toogleEvent(GPIO::High,leds.at(0));
        } else if (event->y() < (dy << 1)) {
            toogleEvent(GPIO::High,leds.at(1));
        } else if (event->y() < ( (dy << 1) + dy ) ) {
            toogleEvent(GPIO::High,leds.at(2));
        } else {
            toogleEvent(GPIO::Low,leds.at(0));
            toogleEvent(GPIO::Low,leds.at(1));
            toogleEvent(GPIO::Low,leds.at(2));
        }
    }
}
//#endif


void Leds::toogleEvent(GPIO::PinState state,GPIO* sender)
{
    //printf("%d toogled to %d\n",sender->pinNumber(),state);
    uchar mask = 0x01 << leds.indexOf(sender);

    m_update |= mask;

    m_state &= ~mask; //limpa estado anterior

    if(state == GPIO::High)
        m_state |= mask;

    update();
}

void Leds::paintEvent(QPaintEvent *)
{
    for (int i = 0; i < m_number ; i++)
    {
        QString key = QString("leds:%1:%2")
                              .arg((m_state >> i) & 0x01)
                              .arg(m_diameter);
        QPixmap pixmap;

        if (!QPixmapCache::find(key, pixmap)) {
            pixmap = generatePixmap((m_state >> i) & 0x01);
            QPixmapCache::insert(key, pixmap);
        }
        QPainter painter(this);
        painter.drawPixmap(0,( i * m_height) / m_number,m_width, m_height / m_number,pixmap);
    }

    m_update = 0x00;
}
