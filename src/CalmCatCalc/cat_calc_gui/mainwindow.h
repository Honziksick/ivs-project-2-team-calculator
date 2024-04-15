/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          mainwindow.h
 * Datum:           8.04.2024
 * Poslední změna:  8.04.2024
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
 * @file mainwindow.h
 * @author Lukáš Farkašovský \<xfarkal00>
 * @brief __Header file pro propojení GUI s matematickou knihovnou__
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
/*přidání matematické knihovny*/
#include "core/cat_calc_core.h"

/**
 * @brief Definice proměnné ""
 * @note
 * Jedná se o prázdný stav, který může nastat ve vice funkcích.
 * Proto je pro něj vymezená vlastní proměnná.
 */
extern QString empty_state;

/**
 * @brief Proměnná ukládající string výsledku
 */
extern QString eq_str;

/**
 * @brief Proměnná s exception
 * @details
 * Proměnná slouží k uložení vyhozeného exceptionu z matematické knihovny.
 * Využívá se ve funkci pro vyhodnocení výrazu. Zachycenou vyjímku zpracuje a
 *  vypíše ji jako ERROR message v terminále.
 */
extern std::exception e;

/**
 * @brief Proměnná pro uložení počtu výskytů čárky
 * @details
 * Používá se k určení, zda je možná k číslu připsat čárku.
 * Pokud není možné napsat čárku, nastaví se na 1, jinak zustává na 0.
 * @note
 * Po vyhodnocení výrazu s funkcí eval() se nastaví zpátky na 0.
 */
extern int comma_rate;

/**
 * @brief Proměnná pro uložení počtu výskytů goniometrických funkcí
 * @details
 * Používá se při práci s gonio. funkcemi. Při prvním použití zabalí
 *  celou hodnotu do závorek. Pokud byly použity počítací funkce jako '+ - / *'
 *  již neobaluje, ale chová se jako normální tlačítko.
 * @note
 * Po vyhodnocení výrazu s funkcí eval() se nastaví zpátky na 0.
 */
extern int gon_rate;

/**
 * @brief Proměnná ukládající zda došlo k zachycení vyjímky
 * @details
 * Pokud došlo k ERRORU z vyjímky, tak se nastaví na 1.
 * @note
 * Funkce pro čísla dokáže smazat ERROR message a nastaví ho zpátky na 0.
 */
extern int err;

/**
 * @brief Proměnná ukládající, pokud došlo k výpočtu
 * @details
 * Pracuje s oběma terminály. Když se vypsal výsledek a chceme s ním dále počítat
 *  tak se nastaví proměnná na 1 a funkce s výpočty pak pracují již s výsledkem.
 */
extern int eq_state;

/**
 * @brief __Makra pro definici bloku NAMESPACE__
 * dále definice třídy MainWindow
 */
QT_BEGIN_NAMESPACE

namespace Ui{
class MainWindow;
}

QT_END_NAMESPACE

/**
 * @class MainWindow
 *
 * @brief třída zdědí vlastnosti QMainWindow
 *
 * @details
 * Q_OBJECT důležíté makro pro třídy, které využívají singály, sloty
 *  a dynamické vlastnosti
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * @brief Deklarace funkcí spojených se signály
     */
private slots:

    /**
     * @brief Signál čísel
     * @details
     * Při stavu, kdy již bylo vypočítán výsledek, toto tlačítko přepíše
     * výraz obsahující celý zadaný příklad
     * Při stavu, kdy došlo ke chybě, tlačítko přepíše chybovou hlášku
     */
    void num();

    /**
     * @brief Signál smazání celého výrazu
     */
    void del();

    /**
     * @brief Signál vypsání levé závroky
     */
    void lbra();

    /**
     * @brief Signál vypsání pravé závorky
     */
    void rbra();

    /**
     * @brief Signál vypsání čárky
     * @details
     * Aby nedošlo k vypsání vicekrát čárky, jsou nastaveny flagy
     * Tyto flagy jsou změněny při zmáčnuktí spojujících tlačítek
     *  +  / * a také po vypsání výsledku pomocí =
     * Při prázdném stavu se nastaví výraz na "0."
     */
    void comma();

    /**
     * @brief Signál pro vypsání výsledku po vyhodnocení výrazu
     * @details
     * Funkce zachytí exceptions vyhozené matematickou knihovnou
     * Při vyhození exceptionu se vypíše Error hlášení do terminálu kalkulačky
     * přesněji tedy do tabulky s výrazem
     * Při prázdném stavu se vypíše výsledek = 0
     * Při neprázdném stavu se vypíše výsledek vyhodnoceného výrazu
     * a nastaví se flag eq_state, který dále pracuje s dalšímy signály
     */
    void equal();

    /**
     * @brief Signál vypsání +
     */
    void plus();

    /**
     * @brief Signál vypsání *
     */
    void multiply();

    /**
     * @brief Signál vypsání
     */
    void minus();

    /**
     * @brief Signál vypsání /
     */
    void div();

    /**
     * @brief Signál vypsání ^
     */
    void root();

    /**
     * @brief Signál vypsání #
     * @warning
     * Musí být napsán vždy ve formátu n#x, kde n značí stupeň odmocniny
     *  a x značí výraz, který je odmocněn
     */
    void sqr();

    /**
     * @brief Signál vypsání !
     */
    void fact();

    /**
     * @brief Signál vypsání sin
     * @details
     * Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void sin();

    /**
     * @brief Signál vypsání cos
     * @details
     * Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void cos();

    /**
     * @brief Signál vypsání tan
     * @details
     * Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void tan();

    /**
     * @brief Signál převedení ze stupňů na radiány a naopak
     * @details
     * Při převedení se změní text tlačítka na současný stav
     */
    void deg_rad();

    /**
     * @brief Signál převedení ze stupňů na radiány a naopak
     * @details
     * Funguje pouze pro horní tabulku s výpočtem, ne s dolní tabulkou s výsledkem
     */
    void delete_char();
};
#endif // MAINWINDOW_H
/*** Konec souboru mainwindow.h ***/
