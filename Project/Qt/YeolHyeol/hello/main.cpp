#include "hello.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hello w;
    w.show();
    return a.exec();
}
