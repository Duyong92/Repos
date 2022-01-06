#include "ProcedureFailureTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcedureFailureTest w;
    w.show();
    return a.exec();
}
