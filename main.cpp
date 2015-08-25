#include <QtGui/QApplication>
#include "mygui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGui w(20,8,8000);
#ifdef HOST_DBG
    w.show();
#else
    w.showFullScreen();
#endif
    
    return a.exec();
}
