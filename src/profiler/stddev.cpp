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
 * 
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

using namespace std;                // standardní knihovna C++
using namespace MathSymbols;        // třídy s matematickými symboly

// Deklarace použitých funkcí z knihovny`stddev.h`
void generateNumbers();
void readData(istream& dataStream, string &valueSum, string &powerSum, int &N);
void readDataFromAutoGenFile(string &valueSum, string &powerSum, int &N);
void readDataFromStdin(string &valueSum, string &powerSum, int &N);
string standardDeviation();


// Inicializace konstatních proměnných (stringů) matematickými operandy/symboly
static const string ADD = ADD_OP;          // Symbol pro sčítání ` + `
static const string SUB = SUB_OP;          // Symbol pro odečítání ` - `
static const string MUL = MUL_OP;          // Symbol pro násobení ` * `
static const string DIV = DIV_OP;          // Symbol pro dělení ` / `
static const string POW = POW_OP;          // Symbol pro mocninu `^2`
static const string ROOT = ROOT_OP;        // Symbol pro odmocninu `2#`
static const string O_BR = O_BRACKET_SYM;  // Symbol pro otevírací závorku `(`
static const string C_BR = C_BRACKET_SYM;  // Symbol pro uzavírací závorku `)`


/*  ~~~ Funkce pro generování náhodných čísel do souboru 'auto_gen.txt' ~~~   */
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


/*            ~~~ Funkce pro načítání čísel z datového proudu ~~~             */
void readData(istream &dataStream, string &valueSum, string &powerSum, int &N){
    string valueX;      // Načtená hodnota ze vstupu (stdin nebo souboru)

    // Cyklus k načtení vstupních dat z datového proudu 
    while(dataStream >> valueX){
        // Pokud je načtená hodnota číslem
        if(stod(valueX)){

            // Konkatenuje hodnotu X k řetězci součtu hodnot X
            valueSum = valueSum + ADD + valueX;

            // Konkatenuje hodnotu X^2 k řetězci součtu druhých mocnin X
            powerSum = powerSum + ADD + (valueX + POW);

            N++;    // Inkrementuje počítadlo načtených hodnot (stringově)
        }
        // Pokud načtená hodnota není číslo, vyhodí výjimku
        else{
            throw invalid_argument("Error: Invalid input data (not a number).");
        }
    }
}


/* ~~~ Funkce pro načítání čísel ze vygenerovaného souboru `auto_gen.txt` ~~~ */
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

/*     ~~~ Funkce pro načítání čísel ze standardního vstupu (`stdin`) ~~~     */
void readDataFromStdin(string &valueSum, string &powerSum, int &N){
    readData(cin, valueSum, powerSum, N);  // čteme ze 'stdin'
}


/*           ~~~ Funkce na výpočet výběrové směrodatné odchylky ~~~           */
string standardDeviation(){
    string valueSum = O_BRACKET_SYM;    // Součet hodnot X ze vstupu
    valueSum = valueSum + "0.0";   
    string powerSum = O_BRACKET_SYM;    // Součet hodnot mocnin X^2 ze vstupu
    powerSum = powerSum + "0.0";
    int N = 0;                          // Sočet načtených hodnot

    // Čti datový proud hodnot ze 'stdin' a zjisti, zda obsahuje alespoň 2 čísla
    readDataFromStdin(valueSum, powerSum, N);

    // Ošetření dělení nulou při nedostatečném vstupu
    if(N < 2){
        // Úklid prostředí pro vygenerovaná data
        valueSum = O_BRACKET_SYM;
        valueSum = valueSum + "0.0";   
        powerSum = O_BRACKET_SYM;
        powerSum = powerSum + "0.0";
        N = 0;

        // Došlo by k dělení nulou -> vygeneruj náhodná čísla na vstup
        generateNumbers();     

        // Čtení vygenerovanychhodnot z 'auto_gen.txt'
        readDataFromAutoGenFile(valueSum, powerSum, N);
    }

    // Uzavření řetězců součtu hodnot a druhých mocnin hodnot
    valueSum = valueSum + C_BRACKET_SYM;
    powerSum = powerSum + C_BRACKET_SYM;

    // Výpočet aritmetického průměru načtených hodnot 
    string mean = valueSum + DIV + to_string(N);

    // Konkatenace matematického výazu pro výpočet radikandu ("pod odmocninou")
    string radicand = (O_BR + (O_BR + (O_BR + "1" + DIV + (O_BR + to_string(N) + SUB + "1" + C_BR) + C_BR) + C_BR) + MUL + (O_BR + powerSum + SUB + (O_BR + to_string(N) + MUL + (O_BR + (O_BR + mean + C_BR) + POW + C_BR) + C_BR) + C_BR) + C_BR);

    // Výpočet výběrové směrodatné odchylky
    string standardDeviation = calculate(ROOT + radicand);

    return standardDeviation;
}


/*                           ~~~ FUNKCE MAIN() ~~~                            */
int main(int argc, char **argv){
    // Výpočet výběrové směrodatné odchylky
    try{
        cout << standardDeviation() << endl;    // Výpis výsledku na 'stdout'
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
