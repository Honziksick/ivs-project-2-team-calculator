/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           main.cpp                                                  *
 * Datum:            08.04.2024                                                *
 * Poslední změna:   19.04.2024                                                *
 *                                                                             *
 * Tým:      Calm CatCalc Coders                                               *
 *                                                                             *
 * Členové:  Farkašovský Lukáš    <xfarkal00>                                  *
 *           Hýža Pavel           <xhyzapa00>                                  *
 *           Kalina Jan           <xkalinj00>                                  *
 *           Krejčí David         <xkrejcd00>                                  *
 *                                                                             *
 ******************************************************************************/
/**
 * @file main.cpp
 * @author Lukáš Farkašovský \<xfarkal00>
 * 
 * @brief Soubor pro otevření okna s UI.
 * @details Tento soubor obsahuje hlavní funkci pro spuštění UI kalkulačky.
 *          Inicializuje a spustí hlavní okno uživatelského rozhraní.
 */

#include "mainwindow.h"
#include <QApplication>


/**
 * @brief Hlavní funkce aplikace.
 * 
 * @details Tato funkce inicializuje aplikaci a vytváří hlavní okno.
 *          Nastavuje název okna a zobrazuje ho.
 * 
 * @param argc Počet argumentů předaných do programu.
 * @param argv Pole argumentů předaných do programu.
 * @return
 * - Vrací návratový kód aplikace.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Calm CatCalc");
    w.show();
    
    return a.exec();
}

/*** Konec souboru main.cpp ***/
