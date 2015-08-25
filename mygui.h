#ifndef MYGUI_H
#define MYGUI_H

#include <QWidget>
#include <QTimer>
#include <QDate>
#include <QDebug>

namespace Ui {
class MyGui;
}

class MyGui : public QWidget
{
    Q_OBJECT
    
public:
    explicit MyGui(unsigned int steps, unsigned int frames, unsigned int period, QWidget *parent = 0);
    ~MyGui();

    void  setSpeed(unsigned int speed);
    
protected:
    void changeEvent(QEvent *e);
    
private:
    const unsigned int SPEED_STEPS          ;
    const unsigned int ANIMATION_FRAMES     ;
    const unsigned int MAX_ANIMATION_PERIOD ;
    const unsigned int MIN_ANIMATION_SPEED  ;

    enum Tabs
    {
        GPIOS,
        ANIMATION,
        INFO
    };

    Ui::MyGui *ui;

    QTimer    *m_animationTimer;

    unsigned int   m_speed;
    unsigned int   m_step;
    bool           m_started;

private slots:
    void updateAnimation();
    void on_startStopButton_clicked();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_birthdayDateEdit_dateChanged(const QDate &date);
    void on_genderComboBox_textChanged(const QString &arg1);
    void on_fpgaCheckbox_stateChanged(int arg1);
    void on_mcuCheckbox_stateChanged(int arg1);
    void on_linuxCheckbox_stateChanged(int arg1);
    void on_androidCheckbox_stateChanged(int arg1);
    void on_iosCheckbox_stateChanged(int arg1);
    void on_windowsCheckbox_stateChanged(int arg1);
    void on_speedControlDial_valueChanged(int value);
};

#endif // MYGUI_H
