#include "leddemowindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDDemoWindow w;
    w.show();
    return a.exec();
}





