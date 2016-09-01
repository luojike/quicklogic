#include "qlmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLMainWindow w;
    w.show();

    return a.exec();
}
