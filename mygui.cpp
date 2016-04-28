#include "mygui.h"
#include "ui_mygui.h"
#include <QListView>


MyGui::MyGui(unsigned int steps,unsigned int frames,unsigned int period,QWidget *parent) :
    SPEED_STEPS(steps),
    ANIMATION_FRAMES(frames),
    MAX_ANIMATION_PERIOD(period),
    MIN_ANIMATION_SPEED(period / frames),
    QWidget(parent),
    ui(new Ui::MyGui)
{
    toogler = new PWM();//Toogler();
    ui->setupUi(this);

    {
        ui->tabWidget->setTabText(ANIMATION,tr("Animation"));

        m_started = false;
        m_step = 1;
        m_speed = MIN_ANIMATION_SPEED;

        m_animationTimer = new QTimer(this);
        m_animationTimer->setInterval(m_speed);
        connect(m_animationTimer,SIGNAL(timeout()),this,SLOT(updateAnimation()));

        ui->animation->setScaledContents(true);
        updateAnimation();

        ui->speedControlDial->setRange(1,SPEED_STEPS);
        ui->speedControlDial->setSingleStep(1);
        ui->speedLabel->setGeometry(ui->speedControlDial->x()+ui->speedControlDial->width()/4,
                                    ui->speedControlDial->y()+ui->speedControlDial->height()/4,
                                    ui->speedControlDial->width()/2,
                                    ui->speedControlDial->height()/2);
    }

    {
        ui->tabWidget->setTabText(INFO,tr("Info"));

        ui->formLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
        ui->formLayout->setLabelAlignment(Qt::AlignLeft);

        ui->genderComboBox->addItem(tr("M"));
        ui->genderComboBox->addItem(tr("F"));
    }

    {
        ui->tabWidget->setTabText(GPIOS,tr("GPIOs"));
        ui->buttons->setGeometry(5*width()/8,height()/3,width()/4,height()/3);
    }

    {
        ui->dutycycle_box->setValue(50);
        ui->dutycycle_box->setSuffix(tr(" %"));
        ui->dutycycle_box->setRange(0,100);
        ui->dutycycle_box->setSingleStep(5);
        ui->dutycycle_box->setFont(QFont("Arial",60));

        ////QSpinBox { border: 3px solid white; border-radius: 5px; }"
        ui->dutycycle_box->setStyleSheet(
                                   "QSpinBox::up-button { width: 60px; height: 60px; }"
                                   "QSpinBox::up-button:hover { width: 60px; height: 60px; }"
                                   "QSpinBox::down-button { width: 60px; height: 60px; }"
                                   "QSpinBox::down-button:hover { width: 60px; height: 60px; }"
                );
    }

//    ui->period_box->setValue(1);
//    ui->period_box->setDecimals(1);
//    ui->period_box->setSingleStep(0.1);
//    ui->period_box->setFont(QFont("Arial",60));
//    ui->period_box->setMinimum(1);

//    ui->pwm_period_unit_box->setStyleSheet("QComboBox { min-height: 220px; min-width: 60px; }"
//                                           "QComboBox QAbstractItemView::item { min-height: 110px; min-width: 60px; }");
//    ui->pwm_period_unit_box->setView(new QListView());
//    ui->pwm_period_unit_box->addItem(tr(" s"));
//    ui->pwm_period_unit_box->addItem(tr(" ms"));
//    ui->pwm_period_unit_box->setFont(QFont("Arial",60));


//    ui->period_box->setStyleSheet("QDoubleSpinBox { border: 3px solid white; border-radius: 5px; }"
//                                  "QDoubleSpinBox::up-button { width: 60px; height: 60px; }"
//                                  "QDoubleSpinBox::up-button:hover { width: 60px; height: 60px; }"
//                                  "QDoubleSpinBox::down-button { width: 60px; height: 60px; }"
//                                  "QDoubleSpinBox::down-button:hover { width: 60px; height: 60px; }"
//            );

    // 1us a 1ms
    ui->period_slider->setRange(1,1000);
    ui->period_slider->setSingleStep(1);
    ui->frequency_value->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
//    ui->period_slider->setStyleSheet("QSlider::handle:horizontal {"
//                                     "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
//                                     "border: 1px solid #0c457e;"
//                                     "width: 30px; height: 20px; margin: -2px 0; border-radius: 3px; }");


    if(toogler->getEnabled()=='1')
    {
        ui->enable_bt->setText(tr("Off"));
    }
    else
    {
        ui->enable_bt->setText(tr("On"));
    }
    //connect(toogler,SIGNAL(toogle()),ui->buttons->keys[0],SLOT(toogle()));
    //toogler->start();
    connect(ui->dutycycle_box,SIGNAL(valueChanged(int)),toogler,SLOT(vSetDutyCycle(int)));
    //connect(ui->period_box,SIGNAL(valueChanged(int)),toogler,SLOT(vSetPeriod(int)));
    //connect(ui->enable_bt,SIGNAL(clicked()),toogler,SLOT(vOnOff()));
}

MyGui::~MyGui()
{
    delete ui;
}

void MyGui::setSpeed(unsigned int speed){
    m_speed = speed;
}

void MyGui::changeEvent(QEvent *e)
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

void MyGui::updateAnimation()
{
    QString m_path = QString().sprintf(":Runner/runner-%02d",m_step) ;
    QPixmap m_pixmap;
    m_pixmap.load(m_path);

    ui->animation->setPixmap(m_pixmap);

    if(++m_step > ANIMATION_FRAMES)
        m_step = 1;
}

void MyGui::on_startStopButton_clicked()
{
    // change activation state
    m_started = !m_started;

    if(m_started){
        m_animationTimer->start();
        ui->startStopButton->setText(tr("Stop"));
    }else{
        m_animationTimer->stop();
        ui->startStopButton->setText(tr("Start"));
    }
}

void MyGui::on_nameLineEdit_textChanged(const QString &arg1)
{

}


void MyGui::on_birthdayDateEdit_dateChanged(const QDate &date)
{

}

void MyGui::on_genderComboBox_textChanged(const QString &arg1)
{

}

void MyGui::on_fpgaCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_mcuCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_linuxCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_androidCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_iosCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_windowsCheckbox_stateChanged(int arg1)
{

}

void MyGui::on_speedControlDial_valueChanged(int value)
{
    m_speed = MIN_ANIMATION_SPEED / value;
    m_animationTimer->setInterval(m_speed);
}

void MyGui::on_enable_bt_clicked()
{
    if(ui->enable_bt->text() == tr("On"))
    {
        ui->enable_bt->setText(tr("Off"));
    }
    else
    {
        ui->enable_bt->setText(tr("On"));
    }
    toogler->vOnOff();
}

//void MyGui::on_pwm_period_unit_box_currentIndexChanged(const QString &arg1)
//{
//    //ui->period_box->setSuffix(arg1);

//    if(arg1 == tr(" s"))
//    {
//        printf("Unit changed to seconds");
//        ui->period_box->setDecimals(1);
//        ui->period_box->setSingleStep(0.1);
//        toogler->vSetPeriod(ui->period_box->text().toDouble()*1000.0);
//    }
//    else
//    {
//        printf("Unit changed to miliseconds");
//        ui->period_box->setDecimals(0);
//        ui->period_box->setSingleStep(1);
//        toogler->vSetPeriod(ui->period_box->text().toDouble());
//    }
//}

//void MyGui::on_period_slider_valueChanged(double arg1)
//{
//    if(ui->pwm_period_unit_box->currentText() == tr(" s"))
//    {
//        printf("Period changed to %f = %f seconds\n",ui->period_box->value(),arg1);
//        toogler->vSetPeriod((int)(1000.0*arg1));
//    }
//    else
//    {
//        printf("Period changed to %f = %f miliseconds\n",ui->period_box->value(),arg1);
//        toogler->vSetPeriod(arg1);
//    }
//}

void MyGui::on_period_slider_valueChanged(int value)
{

    //printf("Period changed to %f nanoseconds\n",1000000.0/value);
    ui->frequency_value->setText(QString::number(value));
    toogler->vSetPeriod(1000000.0/value);

}
