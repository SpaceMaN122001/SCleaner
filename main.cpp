#include "scleaner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SCleaner w;
    w.show();
    return a.exec();
}
