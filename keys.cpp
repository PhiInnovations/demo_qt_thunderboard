#include <QPushButton>
#include <QSpacerItem>
#include <QDebug>
#include "keys.h"
#include "ui_keys.h"

Keys::Keys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keys),
    m_number(2)//, m_btHeight(80)
{
    ui->setupUi(this);

    keys.append(new GPIO( 2 , 15 , GPIO::Out)); //28_CN7
    keys.append(new GPIO( 2 , 24 , GPIO::Out)); //27_CN7

    addPushButton(0);

    for (int i = 1 ; i < m_number ; i++)
    {
        ui->verticalLayout->addSpacerItem(new QSpacerItem(width(),height()/(2*m_number + m_number + 1)));
        addPushButton(i);
    }
    this->setLayout(ui->verticalLayout);
    //qDebug() << (m_btHeight/2)*( 2*m_number + (m_number + 1)) << "vs" << height();
    //this->setGeometry(0,0,width(),(m_btHeight/2)*( 2*m_number + (m_number + 1)));
}

void Keys::addPushButton(int index)
{
    QPushButton* button = new QPushButton(tr("Relay").append(QString(" %1").arg(index+1)));
    button->setFont(QFont("Ubuntu",16));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(button);
    connect(button,SIGNAL(clicked()),keys.at(index),SLOT(toogle()));
}

Keys::~Keys()
{
    delete ui;
}

void Keys::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
