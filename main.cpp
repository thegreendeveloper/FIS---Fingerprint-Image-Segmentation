#include "FIS.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FIS w;
    w.show();

    return a.exec();
}
