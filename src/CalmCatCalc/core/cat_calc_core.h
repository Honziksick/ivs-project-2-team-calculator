#pragma once

#ifndef CAT_CALC_CORE_H_
#define CAT_CALC_CORE_H_

/**
 * @brief použité knihovny
 */
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/**
 * @brief Výčet možných výjimek
*/
enum exceptionCodes{
    // TODO Přidat detailní popis případů vyjímek
    /**
     * @brief Pro špatný zápis výrazu.
     * 
     * @example 64/*8
    */
    SyntaxError = 1,
    /**
     * @brief Pro nesedící páry závorek.
     * 
     * @example 6+8)*2
    */
    ParenthesisMismatch = 2,
    /**
     * @brief Pro neplatné matematické operace.
     * 
     * @example 5/0
     * @example 4.2!
     * @example 10^-2
    */
    MathError = 3,
    /**
     * @brief Pro přetečení maximální hodnoty double.
    */
    Overflow = 4
};


/******************************************************************************
 * Funkce pro práci s výrazy
 * 
******************************************************************************/

/**
 * @brief Výpočet hodnoty zadaného výrazu.
 * 
 * @param[in] expression Výraz, který má být vyhodnocen.
 * @return Výsledek zadaného výrazu v podobě řetězce.
 * @warning Nekontroluje neplatné znaky.
 *          Platné znaky jsou: bílé znaky, čísla, operandy + - * / ^ # s c t
 *          # značí odmocninu, kde 3#27 je třetí odmocnina z 27
 *          s, c, t značí sinus, cosinus a tangens 
 * @exception SyntaxError
 * @exception ParenthesisMismatch
 * @exception MathError
 * @exception Overflow
*/
string calculate(string expression);

/**
 * @brief Kontrola zadaného výrazu.
 * 
 * @param[in] expression Vstupní výraz, který má být zkontrolován.
 * @exception SyntaxError Pro špatný zápis výrazu.
*/
void formatCheck(string expression);

/**
 * @brief Rozděluje vstupní výraz na jednotlivé tokeny.
 * 
 * @param[in] expression Vstupní výraz, který má být rozdělen.
 * @return Vektor s tokeny výrazu.
*/
vector<string> parse(string expression);

/**
 * @brief Převádí vektor tokenů z infixového tvaru na postfixový.
 * 
 * @param[in] parsedExpression Vektor s tokeny výrazu v infixovém tvaru.
 * @return Vektor s tokeny výrazu v postfixovém tvaru.
 * @exception ParenthesesMismatch Pro nesedící páry závorek.
*/
vector<string> postfix(vector<string> parsedExpression);

/**
 * @brief Vyhodnocuje výraz postfixového tvaru.
 * 
 * @param[in] postfixExpression Vektor s tokeny výrazu v postfixovém tvaru.
 * @return Výsledek výrazu v podobě řetězce.
 * @exception MathError Pro neplatné matematické operace jako dělení 0.
*/
string evaluate(vector<string> postfixExpression);



/******************************************************************************
 * Funkce matematických operací
 * 
******************************************************************************/


/**
 * @brief Výpočet absolutní hodnoty zadaného čísla.
 * 
 * @param[in] num Číslo, které má být převedeno na absolutní hodnotu.
 * @return Absolutní hodnota zadaného čísla.
*/
double absVal(double num);

/**
 * @brief Výpočet odmocniny zadaného čísla na zadaný základ.
 * 
 * @param[in] root Základ odmocniny.
 * @param[in] num Číslo, které má být odmocněno.
 * @return Odmocnina zadaného čísla.
 * @exception MathError Pro odmocninu ze záporného čísla se sudým základem
 * @exception MathError Pro odmocninu se záporným základem.
*/
double root(int root, double num);

/**
 * @brief Výpočet mocniny zadaného čísla o zadaném exponentu.
 * 
 * @param[in] exp Exponent mocniny.
 * @param[in] num Základ mocniny.
 * @return Mocnina zadaného čísla.
 * @exception MathError Pro umocňování záporným exponentem.
*/
double power(int exp, double num);

/**
 * @brief Výpočet sinu zadaného čísla.
 * 
 * @param[in] ang Úhel ve stupních.
 * @return Sinus zadaného úhlu.
*/
double csin(double ang);

/**
 * @brief Výpočet cosinu zadaného čísla.
 * 
 * @param[in] ang Úhel ve stupních.
 * @return Cosinus zadaného úhlu.
*/
double ccos(double ang);

/**
 * @brief Výpočet tangens zadaného čísla.
 * 
 * @param[in] ang Úhel ve stupních.
 * @return Tangens zadaného úhlu.
*/
double ctan(double ang);


#endif // CAT_CALC_CORE_H_

/*** Konec souboru cat_calc_core.h ***/
