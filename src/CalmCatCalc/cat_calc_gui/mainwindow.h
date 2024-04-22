/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           mainwindow.h                                              *
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
 * @file mainwindow.h
 * @author Lukáš Farkašovský \<xfarkal00>
 *
 * @brief Soubor s deklaracemi funkcí pro propojení GUI s matematickou knihovnou
 *        _Calm CatCalc Core_.
 * @details Tento hlavičkový soubor obsahuje deklarace funkcí a tříd, které jsou
 *          použity pro propojení uživatelského rozhraní aplikace s matematickou
 *          knihovnou _Calm CatCalc Core_. Zahrnuje třídy pro hlavní okno,
 *          dialogová okna a další prvky uživatelského rozhraní.
 *
 * @see Deklarace funkcí tohoto hlavičkového souboru naleznete v sekci
 *      `Třídy` uvnitř třídy \link MainWindow \endlink.
 */

#pragma once
#ifndef MAINWINDOW_H
/** @cond */
#define MAINWINDOW_H
/** @endcond */

#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>
#include <QLineEdit>

// Přidání matematické knihovny
#include "cat_calc_core.h"
using namespace catMath;

/**
 * @brief Definice proměnné "".
 * @details Jedná se o prázdný stav, který může nastat ve více funkcích.
 *          Z tohoto důvodu je pro něj vymezena vlastní proměnná.
 */
extern QString empty_state;

/**
 * @brief Proměnná ukládající string výsledku.
 */
extern QString eq_str;

/**
 * @brief Proměnná s vyjímkou.
 * @details
 * Proměnná slouží k uložení vyhozeného exceptionu z matematické knihovny.
 * Využívá se ve funkci pro vyhodnocení výrazu. Zachycenou vyjímku zpracuje a
 * vypíše ji jako ERROR message v terminále.
 */
extern std::exception e;

/**
 * @brief Proměnná pro uložení počtu výskytů čárky.
 * @details Používá se k určení, zda je možná k číslu připsat čárku.
 *          Pokud není možné napsat čárku, nastaví se na "1", jinak zustává
 *          na "0".
 * @note
 * - Po vyhodnocení výrazu funkcí `eval()` se nastaví zpátky na "0".
 */
extern int comma_rate;

/**
 * @brief Proměnná pro uložení počtu výskytů goniometrických funkcí.
 * @details Používá se při práci s goniometrickými funkcemi. Při prvním použití
 *          zabalí celou hodnotu do závorek. Pokud byly použity matematické
 *          funkce pro operace `+`, `-`, `/` nebo `*` již neobaluje, ale chová
 *          se jako normální tlačítko.
 * @note
 * - Po vyhodnocení výrazu funkcí `eval()` se nastaví zpátky na "0".
 */
extern int gon_rate;

/**
 * @brief Proměnná ukládající, zda došlo k zachycení vyjímky.
 * @details Pokud byl zaznamenán error z důvodu vyhození vyjímky, nastaví se
 *          na "1".
 * @note
 * - Funkce pro čísla dokáže smazat chybový stav (zpárvu) a nastavit tuto
 *   proměnnou zpět na "0".
 */
extern int err;

/**
 * @brief Proměnná ukládající, pokud došlo k výpočtu.
 * @details Pracuje s oběmy terminály. Když se vypsal výsledek a chceme s ním
 *          dále počítat, tak se nastaví tato proměnná na "1" a matematické
 *          funkce následně pracují s tímto výsledkem.
 */
extern int eq_state;

/** @cond */
QT_BEGIN_NAMESPACE
/** @endcond */

/**
 * @namespace Ui
 * @brief Prostor jmen pro všechny třídy generované nástrojem Qt Designer.
 *
 * @details Tento prostor jmen obsahuje všechny třídy, které byly automaticky
 *          vygenerovány nástrojem Qt Designer. Tyto třídy jsou použity pro
 *          vytvoření a manipulaci s prvky uživatelského rozhraní aplikace.
 *
 * @see Pro více informací o třídě `MainWindow` a jejích funkcích, prosím,
 *      podívejte se na \link MainWindow \endlink.
 */
namespace Ui{
class MainWindow;
}

QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Třída reprezentující hlavní okno aplikace pro propojení signálů s
 *        tlačítky.
 *
 * @details
 * - Třída MainWindow zdědí vlastnosti `QMainWindow` a přidává funkce a sloty
 * pro interakci s uživatelem. Obsahuje metody pro zpracování vstupu od uživatele,
 * výpočet matematických výrazů a zobrazení výsledků.
 * - `Q_OBJECT` je důležité makro pro třídy, které využívají signály, sloty
 * a dynamické vlastnosti. Toto makro umožňuje třídě MainWindow komunikovat
 * s ostatními částmi aplikace pomocí signálů a slotů.
 * - Třída `MainWindow` obsahuje řadu privátních slotů, které jsou navázány
 * na různé uživatelské interakce, jako je stisknutí tlačítka, vstup čísel,
 * smazání výrazu,výpočet výsledku a další.
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy MainWindow.
     *
     * @param parent Ukazatel na rodičovský widget. Defaultně je nastaven na
     *               `nullptr`.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor třídy MainWindow.
     */
    ~MainWindow();

private:
    /**
     * @brief Ukazatel na instanci třídy `MainWindow` v prostoru jmen `Ui`.
     */
    Ui::MainWindow *ui;

private slots:
    /**
     * @brief Slot pro zpracování signálu čísel.
     *
     * @details Při stavu, kdy již bylo vypočítán výsledek, toto tlačítko
     *          přepíše výraz obsahující celý zadaný příklad. Při stavu, kdy
     *          došlo k chybě, tlačítko přepíše chybovou hlášku.
     */
    void num();

    /**
     * @brief Slot pro zpracování signálu smazání celého výrazu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko `del`
     *          pro smazání celého výrazu. Vymaže celý matematický výraz.
     */
    void del();

    /**
     * @brief Slot pro zpracování signálu vypsání levé závorky.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení levé závorky. Vloží levou závorku do výrazu.
     */
    void lbra();

    /**
     * @brief Slot pro zpracování signálu vypsání pravé závorky.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení pravé závorky. Vloží pravou závorku do výrazu.
     */
    void rbra();

    /**
     * @brief Slot pro zpracování signálu vypsání čárky.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení čárky. Aby nedošlo k vypsání čárky vícekrát, jsou
     *          nastaveny flagy. Tyto flagy jsou změněny při stisknutí
     *          spojujících tlačítek `+`, `-`, `/`, `*` a také po vypsání
     *          výsledku pomocí `=`. Při prázdném stavu se nastaví výraz na "0".
     */
    void comma();

    /**
     * @brief Slot pro zpracování signálu vypsání výsledku po vyhodnocení výrazu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          výpočet výsledku. Funkce zachytí exceptions vyhozené
     *          matematickou knihovnou. Při vyhození vyjímky se vypíše chybové
     *          hlášení do terminálu kalkulačky, přesněji tedy do tabulky s
     *          výrazem. Při prázdném stavu se vypíše výsledek = 0. Při
     *          neprázdném stavu se vypíše výsledek vyhodnoceného výrazu a
     *          nastaví se flag `eq_state`, který dále pracuje s dalšími signály.
     *
     * @throws invalid_argument Pokud je výraz neplatný nebo nemůže být
     *         vyhodnocen, funkce vyhodí výjimku typu `invalid_argument`.
     */
    void equal();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru sčítání.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení operátoru sčítání. Vloží operátor @c + do výrazu.
     */
    void plus();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru násobení.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení operátoru násobení. Vloží operátor @c * do výrazu.
     */
    void multiply();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru odečítání.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení operátoru odečítání. Vloží operátor @c - do výrazu.
     */
    void minus();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru dělení.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení operátoru dělení. Vloží operátor @c / do výrazu.
     */
    void div();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru mocniny.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení operátoru mocniny. Vloží operátor @c ^ do výrazu.
     */
    void root();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru odmocniny.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení odmocniny. Vloží symbol @c # do výrazu.
     */
    void sqr();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru faktoriálu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení faktoriálu. Vloží symbol @c ! do výrazu.
     */
    void fact();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru sinu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení sinu. Vloží funkci @c sin() do výrazu.
     *
     * @note Při prázdném stavu se bere, že se počítá goniometrický výraz s "0".
     *       Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu,
     *       bere se, že chceme již použít daný výraz na jiné číslo.
     */
    void sin();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru kosinu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení kosinu. Vloží funkci @c cos() do výrazu.
     *
     * @note Při prázdném stavu se bere, že se počítá goniometrický výraz s "0".
     *       Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu,
     *       bere se, že chceme již použít daný výraz na jiné číslo.
     */
    void cos();

    /**
     * @brief Slot pro zpracování signálu vypsání operátoru tangensu.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          vložení tangensu. Vloží funkci @c tan() do výrazu.
     *
     * @note Při prázdném stavu se bere, že se počítá goniometrický výraz s "0".
     *       Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu,
     *       bere se, že chceme již použít daný výraz na jiné číslo.
     */
    void tan();

    /**
     * @brief Slot pro zpracování signálu převedení ze stupňů na radiány a naopak.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          přepnutí mezi stupni a radiány. Při aktivaci se změní text
     *          tlačítka na současný stav.
     */
    void deg_rad();

    /**
     * @brief Slot pro zpracování signálu smazání posledního znaku v horním
     *        terminálu s výpočtem.
     *
     * @details Tento slot je aktivován, když uživatel stiskne tlačítko pro
     *          smazání posledního znaku. Funguje pouze pro horní tabulku s
     *          výpočtem, ne s dolní tabulkou s výsledkem.
     */
    void delete_char();

}; // class MainWindow

#endif // MAINWINDOW_H

/*** Konec souboru mainwindow.h ***/
