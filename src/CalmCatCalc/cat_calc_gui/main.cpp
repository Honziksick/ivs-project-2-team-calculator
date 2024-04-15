/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          main.cpp
 * Datum:           8.04.2024
 * Poslední změna:  8.04.2024
 *
 * Tým:     Calm CatCalc Coders
 *
 * Autoři:  Farkašovský Lukáš    <xfarkal00>
 *         	Hýža Pavel           <xhyzapa00>
 *         	Kalina Jan           <xkalinj00>
 *         	Krejčí David         <xkrejcd00>
 */
/** @endcond */

/**
 * @file main.cpp
 * @author Lukáš Farkašovský \<xfarkal00>
 * @brief __Soubor pro otevření okna s UI__
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //změna ikony
    a.setWindowIcon(QIcon("paw.png"));
    //změna názvu aplikace
    w.setWindowTitle("Calm CatCalc");
    w.show();
    return a.exec();
}

/*** Konec souboru mainwindow.cpp ***/
