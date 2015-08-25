#include "mygui.h"
#include "ui_mygui.h"


MyGui::MyGui(unsigned int steps,unsigned int frames,unsigned int period,QWidget *parent) :
    SPEED_STEPS(steps),
    ANIMATION_FRAMES(frames),
    MAX_ANIMATION_PERIOD(period),
    MIN_ANIMATION_SPEED(period / frames),
    QWidget(parent),
    ui(new Ui::MyGui)
{
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
