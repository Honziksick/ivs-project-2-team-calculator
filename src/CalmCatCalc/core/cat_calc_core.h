/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           cat_calc_core.h                                           *
 * Datum:            19.03.2024                                                *
 * Poslední změna:   22.04.2024                                                *
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
 * @file cat_calc_core.h
 * @author David Krejčí \<xkrejcd00>
 *
 * @brief Deklarace funkcí matematické knihovny _Calm CatCalc Core_.
 * @details Tento soubor obsahuje deklarace funkcí, které jsou použity
 *          v matematické knihovně _Calm CatCalc Core_. Knihovna poskytuje
 *          základní matematické operace a funkce pro kalkulačku _Calm CatCalc_.
 *
 * @see Deklarace funkcí tohoto hlavičkového souboru naleznete v sekci
 *      `Prostory jmen` u jmenného prostoru \link catMath \endlink.
 *
 * @note __Tabulka vyjímek, které mohou nastat:__ <br>
 * |             Výjimka                |                      Popis                      |
 * | ---------------------------------- | ----------------------------------------------- |
 * | `invalid_argument("Syntax Error")` | Chyba syntaxe v zadaném výrazu.                 |
 * | `invalid_argument("Math Error")`   | Při neplatné matematické operace jako dělení 0. |
 * | `invalid_argument("Parenthesis Mismatch")` | Pro nesedící páry závorek.              |
 * | `overflow_error("Overflow")`       | Při přetečení datových typů.                    |
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
#include <limits>

#define CALC_PRECISION 0.000000000000001  /**< Desetinná přesnost kalkulačky. */
#define MAX_CYCLES 200                /**< Maximální počet aproximací funkcí. */
#define PI 3.14159265358979323846     /**< Hodnota čísla _pí_. */

/**
 * @brief Globání proměnná určující, jestli jsou hodnoty zadány ve stupních.
 *        nebo radiánech
 * @details
 * - `true` = radiány
 * - `false` = stupně
 */
extern bool degRad;

using namespace std;

/**
 * @brief Výčet pro priority operátorů.
 *
 * @details Tento enum definuje priority pro různé operátory používané v
 *          kalkulačce.
 */
enum OperatorPriority{
    PARENTHESES = 0, /**< '(' a ')' mají prioritu 0 */
    ADD_SUB = 1, /**< '+' a '-' mají prioritu 1 */
    MUL_DIV = 2, /**< '*' a '/' mají prioritu 2 */
    OTHERS = 3, /**< všechny ostatní operátory mají prioritu 3 */
    GONIOMETRIC = 4, /**< 's', 'c' a 't' mají prioritu 4 */
    NEGATION = 5 /**< '~' má prioritu 5 */
};


/**
 * @namespace catMath
 * @brief Funkce matematické knihovny _CatCalc Core_.
 *
 * @details Tento jmenný prostor obsahuje všechny matematické funkce a třídy
 *          používané v knihovně CatCalc. Zahrnuje funkce pro základní
 *          matematické operace, jako je sčítání, odečítání, násobení a dělení,
 *          stejně jako funkce pro pokročilejší operace, jako je výpočet
 *          faktoriálů, mocnin, odmocnin či goniometrických funkcí.
 */

namespace catMath{


/*******************************************************************************
 *                                                                             *
 *                          FUNKCE PRO PRÁCI S VÝRAZY                          *
 *                                                                             *
 ******************************************************************************/

/**
 * @brief Výpočet hodnoty zadaného výrazu.
 *
 * @details Funkce zkontroluje, jestli výraz není prázdný, naformátuje ho pomocí
 *          funkce `formatInput()`, převede ho na tokeny pomocí funkce `parse()`
 *          a následně ho převede na postfixový tvar pomocí funkce `postfix()`
 *          Nakonec je výraz vyhodnocen pomocí funkce `evaluate()`.
 *
 * @param[in] expression Výraz, který má být vyhodnocen (v podobě `string`).
 * @return
 * - Řetězec reprezentující výsledek zadaného výrazu.
 * - Pokud výraz neobsahuje žádné číslo, vrátí "0".
 *
 * @warning
 * - Funkce nekontroluje neplatné znaky.
 * @note
 * - __Platné znaky jsou__: bílé znaky, čísla, operandy `+`, `-`, `~`, `*`, `/`,
 * `^`, `#`, `s`, `c` a `t`.
 * - Znak `#` značí odmocninu, kde např. `3#27` je "třetí odmocnina z 27".
 * - Znaky `s`, `c` a `t` značí goniometrické funkce _sinus_, _cosinus_ a
 * _tangens_.
 *
 * @throws invalid_argument("SyntaxError") Pokud je výraz syntakticky nesprávný.
 * @throws invalid_argument("MathError") Pokud dojde k matematické chybě,
 *         například dělení nulou.
 * @throws invalid_argument("ParenthesisMismatch") Pokud počet otevíracích a
 *         uzavíracích závorek ve výrazu nesouhlasí.
 * @throws overflow_error("Overflow") Pokud výsledek výrazu překročí maximální
 *         hodnotu, kterou lze reprezentovat daným datovým typem.
*/

string calculate(string expression);

/**
 * @brief Rozděluje vstupní výraz na jednotlivé tokeny.
 *
 * @details Funkce bere řetězec reprezentující matematický výraz, rozdělí ho na
 *          tokeny, které jsou uloženy v poli, a vrátí ho jako výsledek.
 *
 * @param[in] expression Vstupní výraz, který má být rozdělen (v podobě `string`).
 * @return
 * - Vektor s tokeny výrazu.
 *
 * @note
 * - __Tokeny jsou:__ čísla, operátory a závorky.
 * - Mezery jsou odstraněny.
*/
vector<string> parse(string expression);

/**
 * @brief Převádí vektor tokenů z infixového tvaru na postfixový.
 *
 * @details Funkce prochází každý token v infixovém výrazu. Pokud je token
 *          číslo, tak se přidá do postfixového výrazu. Uzavřená závorka znamená,
 *          že se provedou všechny operace do začátku závorky. Pokud je token
 *          operátor, tak se porovná s operátorem na vrcholu zásobníku. Pokud má
 *          token vyšší prioritu nebo stejnou prioritu s pravou asociativitou,
 *          tak se přidá na zásobník. Jinak se operátory s vyšší nebo stejnou
 *          prioritou a levou asociativitou se odebírají ze zásobníku a
 *          přidávají se do postfixového výrazu. Na konci se přidají všechny
 *          zbývající operátory ze zásobníku.
 *
 * @param[in] parsedExpression Vektor s tokeny výrazu v infixovém tvaru.
 * @return
 * - Vektor s tokeny výrazu v postfixovém tvaru.
 *
 * @throws invalid_argument("ParenthesisMismatch") Pokud počet otevíracích a
 *         uzavíracích závorek ve výrazu nesouhlasí.
*/
vector<string> postfix(vector<string> parsedExpression);

/**
 * @brief Vyhodnocuje výraz postfixového tvaru.
 *
 * @details Fuknce zjednodušuje výraz, dokud nezůstane pouze jedno číslo. Funkce
 *          iteruje přes každý token z vektoru postfixového výrazu. Pokud je
 *          token číslo, tak se přidá na zásobník. Pokud je token operátor, tak
 *          se provede daná operace. Výsledek operace se přidá na zásobník.
 *
 * @param[in] postfixExpression Vektor s tokeny výrazu v postfixovém tvaru.
 * @return
 * - Výsledek výrazu v podobě řetězce.
 *
 * @note
 * - Zásobník je použit pro ukládání mezivýsledků a provádění operací.
 *
 * @throws invalid_argument("SyntaxError") Pokud je výraz syntakticky nesprávný.
*/
string evaluate(vector<string> postfixExpression);

/**
 * @brief Vyhodnotí jednu operaci.
 *
 * @details Tato funkce vyhodnotí zadanou operaci na zásobníku. Operace je
 *          určena operátorem `op`. Operandy pro operaci jsou odebrány ze
 *          zásobníku a výsledek operace je přidán zpět na zásobník. Pokud
 *          operace vyžaduje více operandů, než je na zásobníku, vyhodí se
 *          výjimka. Pokud je zadaný neznámý operátor, vyhodí se také výjimka.
 *
 * @param[in] op Znak vyhodnocované operace.
 * @param[in] stack Ukazatel na zásobník s operandy.
 * @return
 * - Vrací string výsledku operace.
 *
 * @throws invalid_argument("SyntaxError") Pokud je výraz syntakticky nesprávný.
 * @throws invalid_argument("MathError") Pokud dojde k matematické chybě,
 *         například dělení nulou.
*/
string evaluateOperation(char op, vector<string> *stack);


/*******************************************************************************
 *                                                                             *
 *                       FUNKCE PRO MATEMATICKÉ OPERACE                        *
 *                                                                             *
 ******************************************************************************/

/**
 * @brief Vypočítá absolutní hodnotu zadaného čísla.
 *
 * @param[in] num Číslo, které má být převedeno na absolutní hodnotu.
 * @return
 * - Absolutní hodnota zadaného čísla.
*/
double absVal(double num);

/**
 * @brief Vypočítá faktoriál.
 *
 * @details Funkce vypočítá faktoriál zadaného čísla. Pokud je výsledek větší
 *          než maximální veliksot datového typu `size_t`, vyhodí se vyjímka.
 *
 * @param[in] num Číslo, ze kterého se má vypočítat faktoriál.
 * @return
 * - Faktoriál zadaného čísla.
 *
 * @throws overflow_error("Overflow") Pokud výsledek výrazu překročí maximální
 *         hodnotu, kterou lze reprezentovat daným datovým typem.
*/
size_t factorial(size_t num);

/**
 * @brief Funkce na provedení normalizace úhlu.
 *
 * @details Převede úhel do radiánů, pokud je to zapotřebí, a upraví jej na
 *          rozmezí (interval) <0, 2PI>.
 *
 * @param[in] ang Úhel, který se má normalizovat.
 * @return
 * - Normalizovaný úhel.
*/
double normalizeAngle(double ang);

/**
 * @brief Vypočítá odmocninu zadaného čísla pro zadaný základ.
 *
 * @details Funkce vypočítá odmocninu zadaného čísla za využití binárního
 *          vyhledáváním.
 *
 * @param[in] exp Základ odmocniny.
 * @param[in] num Číslo, které má být odmocněno.
 * @return
 * - Odmocnina zadaného čísla.
 *
 * @throws invalid_argument("MathError") Pro odmocninu ze záporného čísla se
 *         sudým základem.
 * @throws invalid_argument("MathError") Pro odmocninu se záporným základem.
*/
double root(int exp, double num);

/**
 * @brief Vypočítá mocninu zadaného čísla o zadaném celém nezáporném exponentu.
 *
 * @param[in] exp Exponent mocniny.
 * @param[in] num Základ mocniny.
 * @return
 * - Mocnina zadaného čísla.
 *
 * @throws invalid_argument("MathError") Pokud je exponent záporný a číslo je
 *         nula.
 * @throws overflow_error("Overflow") Pokud dojde k přetečení při výpočtu.
 */
double power(int exp, double num);

/**
 * @brief Vypočítá sinus zadaného úhlu.
 *
 * @details Funkce vypočítá sinus zadaného úhlu taylorovým polynomem.
 *
 * @param[in] ang Zadaný úhel.
 * @return
 * - Sinus zadaného úhlu.
 *
 * @note
 * - Globální závislost na \link degRad \endlink
*/
double csin(double ang);

/**
 * @brief Vypočítá kosinus zadaného úhlu.
 *
 * @details Funkce vypočítá kosinus zadaného úhlu taylorovým polynomem.
 *
 * @param[in] ang Zadaný úhel.
 * @return Kosinus zadaného úhlu.
 *
 * @note
 * - Globální závislost na \link degRad \endlink
*/
double ccos(double ang);

/**
 * @brief Vypočítá tangens zadaného úhlu.
 *
 * @details Funkce vypočítá tangens zadaného úhlu funkcemi csin a ccos.
 *
 * @param[in] ang Zadaný úhel.
 * @return
 * - Tangens zadaného úhlu.
 *
 * @note
 * - Globální závislost na \link degRad \endlink
 *
 * @throws invalid_argument("MathError") Pokud pro zadaný úhel není funkce
 *         tangens definovaná.
*/
double ctan(double ang);

/**
 * @brief Funkce na výpočet součtu dvou výrazů (v podobě `string`).
 *
 * @details Tato funkce přijímá dva řetězce, které reprezentují čísla, a vrací
 *          jejich součet jako řetězec. Pokud je alespoň jedno z čísel
 *          desetinné, provede se operace s typem `double`. Pokud jsou obě čísla
 *          celá, provede se operace s typem `long long`.
 *
 * @param[in] num1 První předaný operand (v podobě `string`).
 * @param[in] num2 Druhý předaný operand (v podobě `string`).
 * @return
 * - Součet dvou čísel (v podobě `string`).
*/
string evalAdd(string num1, string num2);

/**
 * @brief Funkce na výpočet rozdílu dvou výrazů (v podobě `string`).
 *
 * @details Tato funkce přijímá dva řetězce, které reprezentují čísla, a vrací
 *          jejich rozdíl jako řetězec. Pokud je alespoň jedno z čísel
 *          desetinné, provede se operace s typem `double`. Pokud jsou obě čísla
 *          celá, provede se operace s typem `long long`.
 *
 * @param[in] num1 První předaný operand (v podobě `string`).
 * @param[in] num2 Druhý předaný operand (v podobě `string`).
 * @return
 * - Rozdíl dvou čísel (v podobě `string`).
*/
string evalSub(string num1, string num2);

/**
 * @brief Funkce na výpočet součinu dvou výrazů (v podobě `string`).
 *
 * @details Tato funkce přijímá dva řetězce, které reprezentují čísla, a vrací
 *          jejich součin jako řetězec. Pokud je alespoň jedno z čísel
 *          desetinné, provede se operace s typem `double`. Pokud jsou obě čísla
 *          celá, provede se operace s typem `long long`. Pokud dojde k
 *          přetečení při výpočtu, vyhodí se výjimka overflow_error.

 *
 * @param[in] num1 První předaný operand (v podobě `string`).
 * @param[in] num2 Druhý předaný operand (v podobě `string`).
 * @return
 * - Součin dvou čísel (v podobě `string`).
 *
 * @throws overflow_error("Overflow") Pokud dojde k přetečení při výpočtu.
*/
string evalMul(string num1, string num2);

/**
 * @brief Funkce na výpočet podílu dvou výrazů (v podobě `string`).
 *
 * @details Tato funkce přijímá dva řetězce, které reprezentují čísla, a vrací
 *          jejich podíl jako řetězec. Pokud je alespoň jedno z čísel
 *          desetinné, provede se operace s typem `double`. Pokud jsou obě čísla
 *          celá, provede se operace s typem `long long`. Pokud dojde k
 *          přetečení při výpočtu, vyhodí se výjimka overflow_error.

 *
 * @param[in] num1 První předaný operand (v podobě `string`).
 * @param[in] num2 Druhý předaný operand (v podobě `string`).
 * @return
 * - Podíl dvou čísel (v podobě `string`).
 *
 * @throws invalid_argument("MathError") Pokud je dělitelem nula.
 * @throws overflow_error("Overflow") Pokud dojde k přetečení při výpočtu.
 */
string evalDiv(string num1, string num2);

/**
 * @brief Funkce provede negaci výrazu (v podobě `string`).
 *
 * @details Tato funkce přijímá řetězec, který reprezentuje číslo, a vrací
 *          jeho negativní hodnotu jako řetězec. Pokud je zadané číslo
 *          desetinné, provede se operace s typem `double`. Pokud je zadané
 *          číslo celé, provede se operace s typem `long long`.
 *
 * @param[in] num1 Číslo, jehož negaci chceme provést (v podobě `string`).
 * @return
 * - Negace předaného čísla (v podobě `string`).
*/
string evalNeg(string num1);


/*******************************************************************************
 *                                                                             *
 *                           DALŠÍ VYUŽÍVANÉ FUNKCE                            *
 *                                                                             *
 ******************************************************************************/

/**
 * @brief Kontroluje, zda je zadaný znak operátorem.
 *
 * @details Tato funkce kontroluje, zda je zadaný znak jedním z následujících
 *          operátorů: `+`, `-`, `*`, `/`, `^`, `#`, `!`, `s`, `c`, `t`, `~`.
 *
 * @param[in] c Znak, který se má zkontrolovat.
 * @return
 * - `true`, pokud je zadaný znak operátorem, jinak `false`.
*/
bool isOperator(char c);

/**
 * @brief Vrátí prioritu zadaného operátoru.
 *
 * @details Tato funkce vrátí prioritu zadaného operátoru. Priority operátorů
 *          je definována následovně:
 * - `(` a `)` mají prioritu 0 (největší)
 * - `+` a `-` mají prioritu 1
 * - `*` a `/` mají prioritu 2
 * - všechny ostatní operátory mají prioritu 3
 * - `s`, `c` a `t` mají prioritu 4
 * - `~` má prioritu 5 (nejmenší)
 *
 * @param[in] op Operátor, jehož priorita se má zjistit.
 * @return
 * - Priorita zadaného operátora jako celé číslo.
*/
int priority(string op);

/**
 * @brief Zjistí asociativitu zadaného operátora.
 *
 * @details Funkce vrací asociativitu operace pro převádění na postfixový tvar.
 * Při stejné prioritě se nejdřívem provede operace s asociativitou zprava.
 *
 * @param[in] op Operátor, jehož asociativitu chceme zjistit.
 * @return
 * - `true`, pokud je operátor levě asociativní
 * - `false`, pokud je pravě asociativní.
*/
bool associativity(string op);

/**
 * @brief Převede číslo typu `double` na `string`.
 *
 * @details Funkce převede hodnotu datového typu `double` na datový typ `string`
 *          a provede zaokrouhlení s přesností až na 16 desetinných míst.
 *
 * @param[in] x Číslo typu `double`, které se má převést na řetězec.
 * @return
 * - Řetězec reprezentující zadané číslo.
 *
 * @note
 * - Pokud je číslo celé, vrátí se řetězec bez desetinných míst.
 * - Pokud je číslo desetinné a končí nulami, tyto nuly se odstraní.
 * - Pokud je číslo desetinné a končí devítkami, tyto devítky se zaokrouhlí
 * nahoru.
*/
string doubleToString(double x);

/**
 * @brief Formátuje vstupní výraz pro další zpracování.
 *
 * @details Tato funkce přijímá vstupní výraz jako řetězec a provede následující
 * úpravy: <br>
 * - Odstraní přebytečné mezery.
 * - Uzavře neuzavřené závorky.
 * - Nahradí goniometrické funkce "sin", "cos" a "tan" jejich jednopísmennými
 * ekvivalenty `s`, `c` a `t`.
 * - Přidá implicitní odmocninu 2, pokud je odmocnina bez čísla.
 * - Přidá implicitní mocninu 2, pokud je mocnina bez čísla.
 * Výsledkem je výraz, který je připraven pro další zpracování.
 *
 * @param[in] expression Vstupní výraz jako řetězec.
 * @return
 * - Formátovaný výraz jako řetězec.
*/
string formatInput(string expression);

/**
 * @brief V případě chybějících závorek, provede doplnění párů.
 *
 * @details Tato funkce přijímá vstupní výraz jako řetězec a zkontroluje, zda
 *          jsou všechny otevřené závorky párovány s uzavřenými závorkami. Pokud
 *          je počet otevřených závorek větší než počet uzavřených závorek,
 *          funkce přidá potřebný počet uzavřených závorek na konec výrazu.
 *          Pokud je počet uzavřených závorek větší než počet otevřených
 *          závorek, funkce vyhodí výjimku `invalid_argument`.
 *
 * @param[in] expression Vstupní výraz jako řetězec.
 * @return
 * - Výraz se spárovými závorkami jako řetězec.
 *
 * @throws invalid_argument("ParenthesisMismatch") Pokud je počet uzavřených
 *         závorek větší než počet otevřených závorek.
*/
string pairParenthesis(string expression);

/**
 * @brief Odstraní přebytečné mezery ve vstupním výrazu.
 *
 * @details Tato funkce přijímá vstupní výraz jako řetězec a odstraní z něj
 *          všechny přebytečné mezery. Pokud je ve vstupním výrazu více než
 *          jedna mezera mezi dvěma ne-mezerovými znaky, tyto mezery se nahradí
 *          jednou mezerou. Výsledkem je výraz, který má mezi všemi
 *          ne-mezerovými znaky právě jednu mezeru.
 *
 * @param[in] expression Vstupní výraz jako řetězec.
 * @return
 * - Výraz bez přebytečných mezer jako řetězec.
*/
string removeMultSpaces(string expression);

} // namespace catMath

#endif // CAT_CALC_CORE_H_

/*** Konec souboru cat_calc_core.h ***/
