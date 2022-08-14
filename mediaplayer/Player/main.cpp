#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Bug fix for macos: Menus won't display properly without.
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    MainWindow w;
    w.show();
    return a.exec();
}
