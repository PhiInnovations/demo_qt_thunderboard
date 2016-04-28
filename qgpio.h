#ifndef QGPIO_H
#define QGPIO_H

#include <QDir>
#include <QFile>
#include <list>

using namespace std;

#include <string>

static const string io_output = "out";
static const string io_input = "in";

static const string edge_none = "none";
static const string edge_rising = "rising";
static const string edge_falling = "falling";
static const string edge_both = "both";

class QGpio
{

public:
    explicit QGpio(int gpio_pin);
    ~QGpio(void);

public :
    int gpio_set_direction(const string &direction);
    string gpio_get_direction();
    int gpio_set_value(const string &value);
    string gpio_get_value();
    int gpio_set_edge(const string &edge_name);
    string gpio_get_path();
    int gpio_export(int gpio_pin);

private :
    int gpio_number;            /* The GPIO pin number */
    QDir gpio_directory;        /* Directory controlling this GPIO */
    string io_direction;        /* "out" or "in" */

    
};

#endif // QGPIO_H
