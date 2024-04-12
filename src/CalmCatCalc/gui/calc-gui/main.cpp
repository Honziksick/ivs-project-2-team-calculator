#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /*zmena ikony*/
    a.setWindowIcon(QIcon("paw.png"));
    /*zmena nazvu aplikace*/
    w.setWindowTitle("Calm CatCalc");
    w.show();
    return a.exec();
}
