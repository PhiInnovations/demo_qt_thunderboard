#include "qgpio.h"
#include <QTextStream>

QGpio::QGpio(int gpio_pin) {
    int tentative_gpio_number = gpio_export(gpio_pin);
    if (tentative_gpio_number < 0) {
        abort();
    } else {
        gpio_number = tentative_gpio_number;
        gpio_directory = QDir("/sys/class/gpio/gpio" + QString::number(gpio_number) + "/");
        io_direction = io_input;
    } /* endif */
}

QGpio::~QGpio(void) {
    static const string gpio_unexport_filename = "/sys/class/gpio/unexport";
    // Close the value file descriptor for this GPIO, if one exists

    QFile gpio_unexport(QString::fromStdString(gpio_unexport_filename));
    if (gpio_unexport.open(QIODevice::WriteOnly)) {
        QTextStream unexport_stream(&gpio_unexport);
        unexport_stream << gpio_number;
        gpio_unexport.close();
    } /* endif */
}


int QGpio::gpio_set_direction(const string &direction) {
    int rc = -1;

    QFile direction_file(gpio_directory.path() + "/direction");
    if (!direction_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_direction(&direction_file);
        out_direction << QString::fromStdString(direction);
        direction_file.close();
        rc = 1;
    } /* endif */

    return rc;
}

string QGpio::gpio_get_direction() {
    QFile direction_file(gpio_directory.path() + "/direction");
    QString direction_str;
    if (direction_file.open(QIODevice::ReadOnly)) {
        QTextStream in_direction(&direction_file);
        in_direction >> direction_str;
        direction_file.close();
    } /* endif */
    return direction_str.toStdString();
}

int QGpio::gpio_set_value(const string &value) {
    int rc=-1;

    QFile value_file(gpio_directory.path() + "/value");
    if (!value_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_value(&value_file);
        out_value << QString::fromStdString(value);
        value_file.close();
        rc = 1;
    } /* endif */
    return rc;
}

string QGpio::gpio_get_value() {
    QFile value_file(gpio_directory.path() + "/value");
    unsigned char value = '0';
    string value_str;
    if (value_file.open(QIODevice::ReadOnly)) {
        QDataStream in_value(&value_file);
        in_value >> value;
        value_str = value;
        value_file.close();
    } /* endif */
    return value_str;
}

int QGpio::gpio_set_edge(const string &edge_name) {
    int rc=-1;

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

string QGpio::gpio_get_path() {
    return (gpio_directory.path() + "/value").toStdString();
}

int QGpio::gpio_export(int gpio_pin) {
    static const string gpio_export_filename = "/sys/class/gpio/export";
    int rc = -1;

    gpio_number = gpio_pin;
    if (gpio_number == -1) {
        rc = gpio_number;
    } else {
        QFile gpio_export(QString::fromStdString(gpio_export_filename));
        if (!gpio_export.open(QIODevice::WriteOnly)) {
            rc = -1;
        } else {
            QTextStream export_stream(&gpio_export);
            export_stream << gpio_number;
            gpio_export.close();
            rc = gpio_number;
        } /* endif */
    } /* endif */
    return rc;
}

