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
 * @file stddev.h
 * @author Jan Kalina \<xkalinj00>
 * @brief __Deklarace funkcí pro výpočet výběrové směrodatné odchylky.__
 * @details Deklarované funkce zahrnují načítání dat ze standardního vstupu nebo
 *          ze souboru, výpočet součtu a součtu druhých mocnin načtených hodnot,
 *          a výpočet výběrové směrodatné odchylky. Tento soubor také definuje
 *          také konstanty, a výčtový typ pro návratové hodnoty funkcí.
 */

#pragma once
#ifndef STDDEV_H_

/** @cond */
#define STDDEV_H_
/** @endcond */

#include "../CalmCatCalc/core/cat_calc_core.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>


/**
 * @brief Definice konstant pro generátor náhodných čísel
 */
#define FILE_PATH "auto_gen.txt"  /**< Název generovaného souboru s náhodným daty */
#define AUTO_GEN_NUM  1000        /**< Počet náhodně generovaných čísel */
#define AUTO_GEN_MIN -10000       /**< Nejmenší možná vygenerovaná hodnota */
#define AUTO_GEN_MAX  10000       /**< Největší možná vygenerovaná hodnota */
#define PRECISION 10       /**< Přesnost desetinné části vygenerovaných čísel */


/**
 * @brief Definice konstant (stringů) matematických operací pro funkci
 *        `calculate()`
 */
#define ADD_OP " + "    /**< Operátor sčítání v podobě `string` */
#define SUB_OP " - "    /**< Operátor odčítání v podobě `string` */
#define MUL_OP " * "    /**< Operátor násobení v podobě `string` */
#define DIV_OP " / "    /**< Operátor dělení v podobě `string`  */
#define POW_OP  "^2"    /**< Operátor umocnění na druhou v podobě `string` */
#define ROOT_OP "#2"    /**< Operátor druhé odmocniny v podobě `string` */


/**
 * @brief Definice konstant (znaků) pro závorky
 */

#define O_BRACKET_SYM "("    /**< Otevírací závorka v podobě `string` */
#define C_BRACKET_SYM ")"    /**< Zavírací závorka v podobě `string` */


/**
 * @namespace MathSymbols
 * @brief Obsahuje třídy a konstanty pro matematické symboly
 *
 * @details Tento namespace obsahuje třídy a konstanty pro různé matematické
 *          symboly, které jsou využívány matematickou knihovnou `cat_calc_core`.
 */
namespace MathSymbols{
    /**
     * @class CoreOperands
     * @brief Třída obsahující operandy využívané matematickou knihovnou
     *        `cat_calc_core`.
     *
     * @details Definované konstanty jsou statické, takže mohou být přístupné
     *          bez vytvoření instance třídy CoreOperands.
     */
    class CoreOperands{
    public:
        static const std::string ADD;        /**< Symbol pro sčítání. */
        static const std::string SUB;        /**< Symbol pro odečítání. */
        static const std::string MUL;        /**< Symbol pro násobení. */
        static const std::string DIV;        /**< Symbol pro dělení. */
        static const std::string POW;        /**< Symbol pro mocninu. */
        static const std::string ROOT;       /**< Symbol pro odmocninu. */
    };

    /**
     * @class CoreSymbols
     * @brief Třída obsahující konstanty pro další matematické symboly
     *
     * @details Tyto konstanty jsou statické, takže mohou být přístupné bez
     *          vytvoření instance třídy CoreSymbols.
     */
    class CoreSymbols{
    public:
        static const std::string O_BRACKET;  /**< Symbol pro otevírací závorku. */
        static const std::string C_BRACKET;  /**< Symbol pro uzavírací závorku. */
    };
}


/**
 * @brief Výčtový typ pro návratové hodnoty funkcí
 */
enum returnValues{
    OK,             /**< OK:    Funkce skončila úspěšně */
    E_INV_DATA,     /**< Error: Načtení nečíselné hodnoty */
    E_FILE_OPEN     /**< Error: Nepodařilo se otevřít soubor se vstupními daty */
};


/**
 * @brief Funkce pro generování náhodných čísel do souboru `auto_gen.txt`
 *
 * @details Tato funkce generuje náhodná čísla v rozsahu definovaném konstantami
 *          `PRECISION_MIN` a `PRECISION_MAX` a zapisuje je do souboru určeného
 *          konstantou `FILE_PATH`. Počet generovaných čísel je určen konstantou
 *          `AUTO_GEN_NUM`. Generovaná čísla jsou vypsána na standardní výstup a
 *          zapsána do souboru s pevnou přesností určenou konstantou
 *          `PRECISION`.
 */
void generateNumbers();


/**
 * @brief Funkce pro načítání čísel z datového proudu
 *
 * @details Tato funkce načítá hodnoty ze zadaného datového proudu (může to být
 *          standardní vstup nebo soubor) do doby, dokud jsou k dispozici data.
 *          Pokud načtená hodnota není číslo, funkce vyhodí výjimku typu
 *          `invalid_argument`.
 *
 * @param dataStream Reference na datový proud (`istream`), ze kterého se
 *                   načítají data
 * @param valueSum Reference na řetězec, který uchovává součet načtených hodnot
 * @param powerSum Reference na řetězec, který uchovává součet druhých mocnin
 *                 načtených hodnot
 * @param N Reference na počítadlo načtených hodnot
 *
 * @exception invalid_argument Pokud načtená hodnota není číslo
 */
void readData(istream& dataStream, string &valueSum, string &powerSum, int &N);


/**
 * @brief Funkce pro načítání čísel ze vygenerovaného souboru `auto_gen.txt`
 *
 * @details Tato funkce otevírá soubor určený konstantou `FILE_PATH` a volá
 *          funkci `readData()` s otevřeným souborem jako parametrem, což
 *          umožňuje načítání dat přímo ze souboru. Pokud se soubor nepodaří
 *          otevřít, vypíše chybovou zprávu "Unable to open file".
 *
 * @param valueSum Reference na řetězec, který uchovává součet načtených hodnot
 * @param powerSum Reference na řetězec, který uchovává součet druhých mocnin
 *                 načtených hodnot
 * @param N Reference na počítadlo načtených hodnot
 *
 * @see readData()
 */
void readDataFromAutoGenFile(string &valueSum, string &powerSum, int &N);


/**
 * @brief Funkce pro načítání čísel ze standardního vstupu (`stdin`)
 *
 * @details Tato funkce volá funkci `readData()` s `cin` jako parametrem, což
 *          umožňuje načítání dat přímo ze standardního vstupu. Je určena
 *          k použití, když je program spuštěn s přesměrováním vstupu ze
 *          souboru, například `./stddev < data.txt`.
 *
 * @param valueSum Reference na řetězec, který uchovává součet načtených hodnot
 * @param powerSum Reference na řetězec, který uchovává součet druhých mocnin
 *                 načtených hodnot
 * @param N Reference na počítadlo načtených hodnot
 *
 * @see readData()
 */
void readDataFromStdin(string &valueSum, string &powerSum, int &N);


/**
 * @brief Funkce na výpočet výběrové směrodatné odchylky
 *
 * @details V případě, že je funkce spuštěna jako `./stddev < data.txt`, je
 *          výběrová směrodatná odchylka vypočtena z hodnot v souboru `data.txt`.
 *          V opačném případě je generátor náhodných čísel vygenerován soubor
 *          s daty `auto_gen.txt` a vstup programu je braný právě z tohoto souboru.
 *
 * @note **Vzorec pro výpočet výběrové směrodatné odchylky:**
 *       \f[ s=\sqrt{\frac{1}{N-1}\left(\sum_{i=1}^{N}x_{i}^{2}-
 *           N\overline{x}^{2}\right)} \f]
 *
 * @return `standardDeviation` Výběrová směrodatná odchylka
 */
string standardDeviation();


/**
 * @brief Hlavní funkce programu
 *
 * @details Tato funkce volá funkci `standardDeviation()` pro výpočet výběrové
 *          směrodatné odchylky. Výsledek je vypsán na standardní výstup
 *          (`stdout`). Pokud funkce standardDeviation() vyhodí výjimku typu
 *          `invalid_argument`, chybová zpráva je vypsána na standardní chybový
 *          výstup (`stderr`) a funkce `main()` vrátí `1`. Pokud nedošlo k žádné
 *          chybě, funkce `main()` vrátí `0`.
 *
 * @return OK Pokud nedošlo k žádné chybě
 * @return E_INV_DATA Pokud byla vyhozena výjimku typu `invalid_argument`
 * @return E_FILE_OPEN Pokud byla vyhozena výjimka typu `runtime_error`
 *
 * @exception invalid_argument Pokud funkce `standardDeviation()` vyhodí výjimku
 *            tohoto typu
 * @exception runtime_error Pokud funkce `standardDeviation()` vyhodí výjimku
 *            tohoto typu
 */
int main();


#endif // STDDEV_H_

/*** Konec souboru stddev.h ***/
