/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           stddev.cpp                                                *
 * Datum:            01.04.2024                                                *
 * Poslední změna:   01.04.2024                                                *
 *                                                                             *
 * Tým:      Calm CatCalc Coders                                               *
 *                                                                             *
 * Členové:  Farkašovský Lukáš    <xfarkal00>                                  *
 *           Hýža Pavel           <xhyzapa00>                                  *
 *           Kalina Jan           <xkalinj00>                                  *
 *           Krejčí David         <xkrejcd00>                                  *
 *        	                                                                   *
 ******************************************************************************/
/**
 * @file stddev.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief __Program na výpočet výběrové směrodatné odchylky.__
 * @details TO-DO
 */

#include "../CalmCatCalc/core/cat_calc_core.h"
#include "stddev.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;


double standardDeviation(){
    string valueSum = "0.0";        // Součet hodnot X ze vstupu
    string powerSum = "0.0";        // Součet hodnot mocnin X^2 ze vstupu
    int N = 0;                      // Sočet načtených hodnot

    // Ošetření dělení nulou při nedostatečném vstupu
    if(N < 2){
        // Došlo by k dělení nulou -> vygeneruj náhodná čísla na vstup
        generateNumbers();     

        // Čtení vygenerovanychhodnot z 'auto_gen.txt'
        readDataFromAutoGenFile(valueSum, powerSum, N);
    }
    else{
        // Jiank čtení hodnot ze 'stdin'
        readDataFromStdin(valueSum, powerSum, N);
    }

    // Výpočet aritmetického průměru načtených hodnot 
    string mean = evalDiv(valueSum, doubleToString(N));

    // Výpočet radikandu (tj. "to pod odmocninou")
    string radicand = evalSub(powerSum, evalMul(doubleToString(N), 
                                        doubleToString(power(EXP, stod(mean)))));
    radicand = evalDiv(radicand, doubleToString(N - 1));

    // Výpočet výběrové směrodatné odchylky
    string standardDeviation = doubleToString(root(ROOT, stod(radicand)));

    return stod(standardDeviation);
}


int main(){
    // Výpočet výběrové směrodatné odchylky
    try{
        cout << standardDeviation() << endl;    // výpis výsledku na 'stdout'
    }
    // Funkci byly předány neplatné vstupní hodnoty (tj. nečíselné)
    catch(invalid_argument& error){
        cerr << error.what() << endl;    // Výpis chyby na 'stderr''
        return E_INV_DATA;
    }
    // Nepodařilo se otevřít soubor s vstupními daty
    catch(runtime_error& error){
        cerr << error.what() << endl;    // Výpis chyby na 'stderr'
        return E_FILE_OPEN;
    }

    return OK;
}

/*** Konec souboru stddev.cpp ***/
