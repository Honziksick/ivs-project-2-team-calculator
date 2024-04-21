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

// Pokud je `DEBUG` definováno, makro `LOG` bude aktivní (jinak ne)
//#define DEBUG

#include "cat_calc_core.h"
#include "stddev.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <regex>

using namespace std;                // funkce standardní knihovny C++
using namespace catMath;            // funkce matematické knihovny 'cat_calc_core'
using namespace catStddev;          // funkce pro zpracování dat programu 'stddev'
using namespace MathSymbols;        // třídy s matematickými symboly


// Deklarace použitých funkcí z knihovny`stddev.h`
void catStddev::generateNumbers();
void catStddev::readData(istream& dataStream, string &valueSum, string &powerSum, unsigned long &N);
void catStddev::readDataFromAutoGenFile(string &valueSum, string &powerSum, unsigned long &N);
void catStddev::readDataFromStdin(string &valueSum, string &powerSum, unsigned long &N);
string catStddev::standardDeviation();


// Inicializace konstatních proměnných (stringů) matematickými operandy/symboly
static const string ADD = ADD_OP;          // Symbol pro sčítání ` + `
static const string SUB = SUB_OP;          // Symbol pro odečítání ` - `
static const string MUL = MUL_OP;          // Symbol pro násobení ` * `
static const string DIV = DIV_OP;          // Symbol pro dělení ` / `
static const string POW = POW_OP;          // Symbol pro mocninu `^2`
static const string ROOT = ROOT_OP;        // Symbol pro odmocninu `2#`
static const string O_BR = O_BRACKET_SYM;  // Symbol pro otevírací závorku `(`
static const string C_BR = C_BRACKET_SYM;  // Symbol pro uzavírací závorku `)`


/*            ~~~ Funkce na výpis nápovědy k programu `stddev` ~~~            */
void catStddev::help() {
    printf("       ~~~ STDDEV: The sample standard deviation calculator & profiler ~~~       \n\n");

    // Synopsis
    printf("SYNOPSIS:\n");
    printf("  ./stddev < data_file\n\n");

    // Popis
    printf("DESCRIPTION:\n");
    printf("  -> This program reads numerical values from the standard input or from\n");
    printf("     a file and calculates their sample standard deviation.\n");
    printf("  -> If the read value is invalid (e.g., not a number), the program throws\n");
    printf("     an exception.\n");
    printf("  -> The program supports the following ways of input:\n");
    printf("     - empty (the program generates its own data with Auto-Gen function)\n");
    printf("     - file redirected to STDIN using '<' operator\n\n");

    // Příklady užití
    printf("USAGE EXAMPLES:\n");
    printf("  $ ./stddev\n");
    printf("    -> The program generates its own data and calculates the sample standard\n");
    printf("       deviation\n");
    printf("\n");
    printf("  $ ./stddev data.txt\n");
    printf("    -> The program reads data from the 'data.txt' file and calculates the sample\n");
    printf("       standard deviation.\n");
    printf("\n");
    printf("  $ cat data.txt | ./stddev\n");
    printf("    -> The program reads data from the 'data.txt' file using input redirection\n");
    printf("\n");
    printf("  $ echo \"1 2 3 4 5\" | ./stddev\n");
    printf("    -> The program reads data from the given text string using input redirection\n\n");

    // Nápověda pro autogen
    printf("AUTO-GENERATOR:\n");
    printf("  -> If no input data are provided, automatic generator is launched:\n");
    printf("  -> The generated inpit data will be saved to the 'build/profiling/auto_gen.txt'\n");
    printf("     file.\n");
    printf("\n");
    printf("  $ ./stddev\n");
    printf("    -> %d numbers will be generated from the interval < %d; %d > with\n",
                  AUTO_GEN_NUM, AUTO_GEN_MIN, AUTO_GEN_MAX);
    printf("      precision to %d digits in total.\n\n", PRECISION);

    // Chybové kódy
    printf("RETURN VALUES:\n");
    printf("  0 - Success\n");
    printf("  1 - ERROR: Invalid input values (e.g., non-numerical)\n");
    printf("  2 - ERROR: Unable to open input data file\n\n");
}


/*  ~~~ Funkce pro generování náhodných čísel do souboru 'auto_gen.txt' ~~~   */
void catStddev::generateNumbers(){
    LOG0("    Generating random numbers...");

    ofstream file;            // Vytvoření objektu pro zápis do souboru
    file.open(FILE_PATH);	  // Otevření soubor pro generované hodnoty pro zápis

    // Inicializace generátoru náhodných čísel
    random_device rd;
    mt19937 gen(rd());

    // Definice rozsahu, z jakého se mají generovat náhodná čísla
    uniform_real_distribution<> dis(AUTO_GEN_MIN, AUTO_GEN_MAX);

    // Proměnná pro zobrazení stavu generování náhodných čísel
    int progressBar = AUTO_GEN_NUM / 10;    // Jeden krok pro 10% pokroku
    
    cout << "Launching Auto-Gen, generating "
         << AUTO_GEN_NUM << " random numbers: " << endl;

    // Generujeme tolik čísel, kolik udává konstanta 'AUTO_GEN_NUM'
    for(unsigned long i = 0; i < AUTO_GEN_NUM; i++){
        // Generování náhodného čísla
        double autoGenNum = dis(gen);

        // Zápis náhodného čísla do souboru s přesností určenou 'PRECISION'
        file << fixed << setprecision(PRECISION) << autoGenNum << endl;

        // Aktualizace progress baru po každých 10%
        if (i % progressBar == 0) {
            cout << "\rProgress: " << i/progressBar*10 << "% completed" << flush;
        }
    }

    // Generování hodnot dokončeno
    cout << "\rProgress: 100% completed" << endl;
    
    file.close();
}


/*            ~~~ Funkce pro načítání čísel z datového proudu ~~~             */
void catStddev::readData(istream &dataStream, string &valueSum, string &powerSum, unsigned long &N){
    LOG0("  Reading input data...");

    string valueX;      // Načtená hodnota ze vstupu (stdin nebo souboru)

    // Cyklus k načtení vstupních dat z datového proudu 
    while(dataStream >> valueX){
        try {
            // Pokud je načtená hodnota číslem (+ navíc speciální ošetření nulu)
            if(stod(valueX) || regex_match(valueX, regex("-?0*\\.?0*"))){

                // Přičtení hodnoty X k řetězci součtu hodnot X
                valueSum = calculate(O_BR + valueSum + C_BR + 
                                     ADD + 
                                     O_BR + valueX + C_BR);

                // Přičtení hodnoty X^2 k řetězci součtu druhých mocnin X
                powerSum = calculate(powerSum + ADD + (valueX + POW));

                N++;    // Inkrementuje počítadlo načtených hodnot

                /* LOGOVÁNÍ NAČÍTÁNÍ VSTUPNÍCH DAT */
                LOG("    Read: valueX = %-10s    N = %-6ld    "
                                "valueSum = %-21s    powerSum = %-21s", 
                    valueX.c_str(), N, valueSum.c_str(), powerSum.c_str());
            }
        }
        // Funkci byly předány neplatné vstupní hodnoty (tj. nečíselné)
        catch (const invalid_argument &ia){
            cerr << "Error: Invalid input data (not a number)." << endl;
            exit(E_INV_DATA);
        }
    }
}


/* ~~~ Funkce pro načítání čísel ze vygenerovaného souboru `auto_gen.txt` ~~~ */
void catStddev::readDataFromAutoGenFile(string &valueSum, string &powerSum, unsigned long &N){
    LOG0("Going to read data from 'auto_gen.txt'...");
    ifstream dataFile(FILE_PATH);    // Otevření souboru s náhodnými hodnotami

    try {
        // Pokud se podařilo otevřít soubor, čti z něj vstupní data
        if(dataFile.is_open()){
            readData(dataFile, valueSum, powerSum, N);
            dataFile.close();
        }
    }
    // Nepodařilo se otevřít soubor s vstupními daty
    catch(const runtime_error &re){
        cerr << "Error: Unable to open data file." << endl;
        exit(E_FILE_OPEN);
    }
}

/*     ~~~ Funkce pro načítání čísel ze standardního vstupu (`stdin`) ~~~     */
void catStddev::readDataFromStdin(string &valueSum, string &powerSum, unsigned long &N){
    LOG0("Reading data from 'STDIN'...");
    readData(cin, valueSum, powerSum, N);  // čteme ze 'stdin'
}


/*           ~~~ Funkce na výpočet výběrové směrodatné odchylky ~~~           */
string catStddev::standardDeviation(){
    string valueSum = "0.0";        // Součet hodnot X ze vstupu
    string powerSum = "0.0";        // Součet hodnot mocnin X^2 ze vstupu
    unsigned long N = 0;            // Součet načtených hodnot

    // Čti datový proud hodnot ze 'stdin' a zjisti, zda obsahuje alespoň 2 čísla
    readDataFromStdin(valueSum, powerSum, N);

    // Ošetření dělení nulou při nedostatečném vstupu
    if(N < 2){
        LOG0("  Less than 2 numbers passed to STDIN.");

        // Úklid prostředí pro vygenerovaná data
        valueSum = valueSum + "0.0";   
        powerSum = powerSum + "0.0";
        N = 0;

        // Došlo by k dělení nulou -> vygeneruj náhodná čísla na vstup
        generateNumbers();

        // Čtení vygenerovaných hodnot z 'auto_gen.txt'
        readDataFromAutoGenFile(valueSum, powerSum, N);
    }

    // Výpočet aritmetického průměru načtených hodnot - mat. výraz a výpočet
    string meanExp = O_BR + valueSum + DIV + to_string(N) + C_BR;
    string meanVal = calculate(meanExp);
    string meanPowVal = calculate(meanVal + POW);

    // Výpočet podílu "1/(N-1)" - matematický výraz a výpočet
    string fractionExp = "1" + DIV +                   
                         (O_BR + to_string(N) + SUB + "1" + C_BR);
    string fractionVal = calculate(fractionExp);

    // Výpočet radikandu ("pod odmocninou") - matematický výraz a výpočet
    string radicandExp = (O_BR +
                             (O_BR + fractionVal + C_BR) + MUL +
                           (O_BR +
                             (O_BR + powerSum + C_BR) +
                             SUB +
                               to_string(N) +
                               MUL + 
                               (O_BR + 
                                 meanPowVal +
                               C_BR) +
                            C_BR) +
                         C_BR);
    string radicandVal = calculate(radicandExp);

    // Výpočet výběrové směrodatné odchylky
    string standardDeviation = calculate(ROOT + radicandVal);

    /* LOGOVÁNÍ VÝPOČTU VÝBĚROVÉ SMĚRODATNÉ ODCHLKY */
    LOG0("Prepared mathematical expressions:");
    LOG("  State: valueSum = %-15s", valueSum.c_str());
    LOG("         powerSum = %-15s", powerSum.c_str());
    LOG("                N = %ld\n", N);
    LOG("          meanExp = %s", meanExp.c_str());
    LOG("          meanVal = %-15s", meanVal.c_str());
    LOG("       meanPowVal = %-15s\n", meanPowVal.c_str());
    LOG("      fractionExp = %s", fractionExp.c_str());
    LOG("      fractionVal = %-15s\n", fractionVal.c_str());
    LOG("      radicandExp = %s", radicandExp.c_str());
    LOG("      radicandVal = %-15s\n", radicandVal.c_str());
    LOG("           RESULT = %-15s\n", standardDeviation.c_str());

    return standardDeviation;
}


/*                           ~~~ FUNKCE MAIN() ~~~                            */
int main(int argc, char **argv){
    // Zpracování přepínačů - zda-li chceme vypsat nápovědu
    // Pozn. 1: Nepřipouštíme žádné jiné přepínače, proto 'argc == 2'
    // Pozn. 2: Nápověda je tedy vždy prvním přepínačem, proto 'argv[1]'
    if(argc == 2){
        string arg = argv[1];    // Přepínač pro výpis nápovědy

        if(arg == "-h" || arg == "--help"){
            help();  

            return 0;   // Zavolání funkce help a ukončení programu
        }
    }

    // Výpočet výběrové směrodatné odchylky
    cout << standardDeviation() << endl;    // výpis výsledku na 'stdout'

    return OK;    // Program skončil úspěšně
}

/*** Konec souboru stddev.cpp ***/
