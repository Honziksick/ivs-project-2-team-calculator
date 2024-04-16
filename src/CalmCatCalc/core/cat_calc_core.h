/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          cat_calc_core.h
 * Datum:           19.03.2024
 * Poslední změna:  16.04.2024
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
 * @file cat_calc_core.h
 * @author David Krejčí \<xkrejcd00>
 * @brief __Deklarace funkcí matematické knihovny Calm CatCalc Core.__
 * @details _Tento soubor obsahuje deklarace funkcí, které jsou použity
 * v matematické knihovně Calm CatCalc Core. Knihovna poskytuje základní
 * matematické operace a funkce pro kalkulačku Calm CatCalc._
 */

#pragma once
#ifndef CAT_CALC_CORE_H_

/** @cond */
#define CAT_CALC_CORE_H_
/** @endcond */

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

/** @brief Přesnost kalkulačky */
#define CALC_PRECISION 0.000000000000001

/** @brief Maximální počet aproximací funkcí. */
#define MAX_CYCLES 200

/** @brief Hodnota konstanty PI. */
#define PI 3.14159265358979323846

/**
 * @brief Globání proměnná určující, jestli jsou hodnoty zadány ve stupních nebo radiánech
 * @details
 * - __FALSE__ = stupně
 * - __TRUE__ = radiány
 */
extern bool degRad;

using namespace std;

/**
 * @brief Výčet možných výjimek
 *
 * invalid_argument("Syntax error")
 *
 * invalid_argument("Math error") pro neplatné matematické operace jako dělení 0
 *
 * overflow_error("Overflow") pro přetečení datových typů
 *
 * invalid_argument("Parenthesis mismatch") pro nesedící páry závorek
 *
*/



/******************************************************************************
 * Funkce pro práci s výrazy
 *
******************************************************************************/

/**
 * @brief Výpočet hodnoty zadaného výrazu.
 *
 * @param[in] expression Výraz, který má být vyhodnocen.
 * @return Výsledek zadaného výrazu v podobě řetězce.
 * @warning
 * - Nekontroluje neplatné znaky.
 * @note
 * - <b>Platné znaky jsou</b>: bílé znaky, čísla, operandy '<b>+</b>',
 * '<b>-</b>', '<b>~</b>', '<b>*</b>', '<b>/</b>', '<b>^</b>', '<b>#</b>',
 * '<b>s</b>', '<b>c</b>' a '<b>t</b>'.
 * - Znak '<b>#</b>' značí odmocninu, kde "3#27" je "třetí odmocnina z 27".
 * - Znaky '<b>s</b>', '<b>c</b>' a '<b>t</b>' značí <i>sinus</i>, <i>cosinus</i>
 * a <i>tangens</i>.
 * @exception SyntaxError
 * @exception ParenthesisMismatch
 * @exception MathError
 * @exception Overflow
*/
string calculate(string expression);

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
 * @exception invalid_argument("Parenthesis mismatch") Pro nesedící páry závorek.
*/
vector<string> postfix(vector<string> parsedExpression);

/**
 * @brief Vyhodnocuje výraz postfixového tvaru.
 *
 * @param[in] postfixExpression Vektor s tokeny výrazu v postfixovém tvaru.
 * @return Výsledek výrazu v podobě řetězce.
 * @exception invalid_argument("Math error") Pro neplatné matematické operace jako dělení 0.
*/
string evaluate(vector<string> postfixExpression);

/**
 * @brief Vyhodnotí jednu operaci.
 *
 * @param[in] op Znak vyhodnocované operace.
 * @param[in] stack Ukazatel na zásobník s operandy.
 * @return Vrací string výsledku operace.
 * @exception invalid_argument("Syntax error") pokud zásobník nemá potřebné operandy.
 * @exception invalid_argument("Math error") pokud se má vyhodnotit neplatná operace.
*/
string evaluateOperation(char op, vector<string> *stack);



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
 * @brief Výpočet faktoriálu.
 *
 * @param[in] num Číslo, ze kterého se má získat faktoriál.
 * @return Faktoriál zadaného čísla.
 * @exception Overlow, pokud se výsledek nevejde do 8 bytů.
*/
size_t factorial(size_t num);

/**
 * @brief Normalizace úhlu.
 *
 * @param[in] ang Úhel, který se má normalizovat.
 * @return Normalizovaný úhel.
*/
double normalizeAngle(double ang);

/**
 * @brief Výpočet odmocniny zadaného čísla na zadaný základ.
 *
 * @param[in] root Základ odmocniny.
 * @param[in] num Číslo, které má být odmocněno.
 * @return Odmocnina zadaného čísla.
 * @exception MathError Pro odmocninu ze záporného čísla se sudým základem.
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
 * @brief Výpočet sinu zadaného úhlu.
 *
 * @param[in] ang Zadaný úhel.
 * @note __Globální závislost na__ \link degRad \endlink: FALSE, pokud je úhel zadaný ve stupních, TRUE pro radiány.
 * @return Sinus zadaného úhlu.
*/
double csin(double ang);

/**
 * @brief Výpočet cosinu zadaného úhlu.
 *
 * @param[in] ang Zadaný úhel.
 * @note __Globální závislost na__ \link degRad \endlink: FALSE, pokud je úhel zadaný ve stupních, TRUE pro radiány.
 * @return Cosinus zadaného úhlu.
*/
double ccos(double ang);

/**
 * @brief Výpočet tangens zadaného úhlu.
 *
 * @param[in] ang Zadaný úhel.
 * @note __Globální závislost na__ \link degRad \endlink: FALSE, pokud je úhel zadaný ve stupních, TRUE pro radiány.
 * @return Tangens zadaného úhlu.
 * @exception MathError, pokud v zadaném úhlu není funkce definovaná.
*/
double ctan(double ang);

/**
 * @brief Součet 2 stringů.
*/
string evalAdd(string num1, string num2);

/**
 * @brief Rozdíl 2 stringů.
*/
string evalSub(string num1, string num2);

/**
 * @brief Násobek 2 stringů.
*/
string evalMul(string num1, string num2);

/**
 * @brief Podíl 2 stringů.
*/
string evalDiv(string num1, string num2);

/**
 * @brief Negace stringu.
*/
string evalNeg(string num1);

/******************************************************************************
 * Ostatní funkce
 *
******************************************************************************/

/**
 * @brief Je zadaný znak operátor
 * @return True, pokud je znak operátor, jinak false
*/
bool isOperator(char c);

/**
 * @brief Priorita operace.
 *
 * @param[in] op Operace, jejíž priorita se má zjistit.
 * @return Priorita operace.
*/
int priority(string op);

/**
 * @brief Asociativita operace.
 *
 * @param[in] op Operace, jejíž asociativita se má zjistit.
 * @return True pro asociativitu zleva. False pro zprava.
*/
bool associativity(string op);

/**
 * @brief Převod double na string.
*/
string doubleToString(double x);

/**
 * @brief Formátování vstupního výrazu.
 * 
 * @param[in] expression Vstupní výraz jako string.
 * @return Vrací upravený výraz, jako string.
*/
string formatInput(string expression);

/**
 * @brief Přidává chybějící závorky.
 * 
 * @param[in] expression Vstupní výraz jako string.
 * @return Vrací upravený výraz, jako string.
*/
string pairParenthesis(string expression);

/**
 * @brief Odstraní přebytečné mezery ve výrazu.
 * 
 * @param[in] expression Vstupní výraz jako string.
 * @return Vrací upravený výraz, jako string.
*/
string removeMultSpaces(string expression);


#endif // CAT_CALC_CORE_H_

/*** Konec souboru cat_calc_core.h ***/
