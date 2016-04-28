#ifndef KEYS_H
#define KEYS_H

#include <QWidget>
#include "gpio_ctrl.h"

namespace Ui {
class Keys;
}

class Keys : public QWidget
{
    Q_OBJECT
    
public:
    explicit Keys(QWidget *parent = 0);
    ~Keys();


    // get attributes
    int numberOfKeys() const { return m_number; }

    // set attributes
    void setKeyNumber (int keyNb) { m_number = keyNb; }
    
protected:
    void changeEvent(QEvent *e);

private:
    Ui::Keys *ui;
    QList<GPIO*>    keys;

    int m_number;

    void addPushButton(int index);
};

#endif // KEYS_H
