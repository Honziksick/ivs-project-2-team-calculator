/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           stddev.cpp                                                *
 * Datum:            01.04.2024                                                *
 * Poslední změna:   09.04.2024                                                *
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
 * @details Tento program načítá číselné hodnoty ze standardního vstupu
 *          nebo ze souboru a počítá jejich výběrovou směrodatnou
 *          odchylku. Pokud je načtená hodnota neplatná (např. není číslo),
 *          program vyhodí výjimku. Program dále podporuje načítání dat ze
 *          souboru pomocí přesměrování vstupu. V případě opomenutí předání
 *          vstupních dat si program vygeneruje své vlastní hodnoty a ty
 *          následně využije jako vstupní data. Výsledná směrodatná odchylka je
 *          vypsána na standardní výstup.
 */

#include "../CalmCatCalc/core/cat_calc_core.h"
#include "stddev.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;


void generateNumbers(){
    ofstream file;            // Vytvoření objektu pro zápis do souboru
    file.open(FILE_PATH);	  // Otevření soubor pro generované hodnoty pro zápis

    // Inicializace generátoru náhodných čísel
    random_device rd;
    mt19937 gen(rd());

    // Definice rozsah, z jakého se mají generovat náhodná čísla
    uniform_real_distribution<> dis(AUTO_GEN_MIN, AUTO_GEN_MAX);

    // Generujeme tolik čísel, kolik udává konstanta 'AUTO_GEN_NUM'
    for(int i = 0; i < AUTO_GEN_NUM; i++){
        // Generování náhodného čísla
        double autoGenNum = dis(gen);

        // Zápis náhodného čísla do souboru s přesností určenou 'PRECISION'
        file << fixed << setprecision(PRECISION) << autoGenNum << endl;
    }
    
    file.close();
}


void readData(istream &dataStream, string &valueSum, string &powerSum, int &N){
    string valueX;      // Načtená hodnota ze vstupu (stdin nebo souboru)

    // Cyklus k načtení vstupních dat z datového proudu 
    while(dataStream >> valueX){
        // Pokud je načtená hodnota číslem
        if(stod(valueX)){

            // Přičte hodnotu X k součtu hodnot
            valueSum = evalAdd(valueSum, valueX);

            // Přičte hodnotu X^2 k součtu druhých mocnin
            powerSum = evalAdd(powerSum, doubleToString(power(EXP, stod(valueX))));

            N++;    // Inkrementuje počítadlo načtených hodnot
        }
        // Pokud načtená hodnota není číslo, vyhodí výjimku
        else{
            throw invalid_argument("Error: Invalid input data (not a number).");
        }
    }
}


void readDataFromAutoGenFile(string &valueSum, string &powerSum, int &N){
    ifstream dataFile(FILE_PATH);    // Otevření souboru s náhodnými hodnotami

    // Pokud se podařilo otevřít soubor, čti z něj vstupní data
    if(dataFile.is_open()){
        readData(dataFile, valueSum, powerSum, N);
        dataFile.close();
    }
    // Pokud se nepodařilo otevřít soubor, vyhoď vyjímku
    else{
        throw runtime_error("Error: Unable to open data file.");
    }
}


void readDataFromStdin(string &valueSum, string &powerSum, int &N){
    readData(cin, valueSum, powerSum, N);  // čteme ze 'stdin'
}


double standardDeviation(){
    string valueSum = "0.0";        // Součet hodnot X ze vstupu
    string powerSum = "0.0";        // Součet hodnot mocnin X^2 ze vstupu
    int N = 0;                      // Sočet načtených hodnot

    // Čti datový proud hodnot ze 'stdin' a zjisti, zda obsahuje alespoň 2 čísla
    readDataFromStdin(valueSum, powerSum, N);

    // Ošetření dělení nulou při nedostatečném vstupu
    if(N < 2){
        // Úkolid prostředí pro vygenerovaná data
        valueSum = "0.0";
        powerSum = "0.0"; 
        N = 0;

        // Došlo by k dělení nulou -> vygeneruj náhodná čísla na vstup
        generateNumbers();     

        // Čtení vygenerovanychhodnot z 'auto_gen.txt'
        readDataFromAutoGenFile(valueSum, powerSum, N);
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
