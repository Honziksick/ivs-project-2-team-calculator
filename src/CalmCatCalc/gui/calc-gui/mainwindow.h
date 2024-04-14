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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>
#include <QLineEdit>
/*přidání matematické knihovny*/
#include "../../core/cat_calc_core.h"

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
 * @note Q_OBJECT důležíté makro pro třídy, které využívají singály, sloty
 *      a dynamické vlastnosti
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
     * @note
     * -Při stavu, kdy již bylo vypočítán výsledek, toto tlačítko přepíše
     * výraz obsahující celý zadaný příklad
     * -Při stavu, kdy došlo ke chybě, tlačítko přepíše chybovou hlášku
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
     * @note
     * -Aby nedošlo k vypsání vicekrát čárky, jsou nastaveny flagy
     * -Tyto flagy jsou změněny při zmáčnuktí spojujících tlačítek
     *  + - / * a také po vypsání výsledku pomocí =
     * -Při prázdném stavu se nastaví výraz na "0."
     */
    void comma();

    /**
     * @brief Signál pro vypsání výsledku po vyhodnocení výrazu
     * @note
     * -Funkce zachytí exceptions vyhozené matematickou knihovnou
     * -Při vyhození exceptionu se vypíše Error hlášení do terminálu kalkulačky
     * přesněji tedy do tabulky s výrazem
     * -Při prázdném stavu se vypíše výsledek = 0
     * -Při neprázdném stavu se vypíše výsledek vyhodnoceného výrazu
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
     * @brief Signál vypsání -
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
     * -Musí být napsán vždy ve formátu n#x, kde n značí stupeň odmocniny
     *  a x značí výraz, který je odmocněn
     */
    void sqr();

    /**
     * @brief Signál vypsání !
     */
    void fact();

    /**
     * @brief Signál vypsání sin
     * @note
     * -Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * -Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void sin();

    /**
     * @brief Signál vypsání cos
     * @note
     * -Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * -Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void cos();

    /**
     * @brief Signál vypsání tan
     * @note
     * -Při prázdném stavu se bere, že se počítá goniometrický výraz s 0
     * -Pokud je jakýkoliv goniometrický výraz použit ve stejném výpočtu
     *  bere se, že chceme již použit daný výraz na jiné číslo
     */
    void tan();

    /**
     * @brief Signál převedení ze stupňů na radiány a naopak
     * @note
     * -Při převedení se změní text tlačítka na současný stav
     */
    void deg_rad();

    /**
     * @brief Signál převedení ze stupňů na radiány a naopak
     * @note
     * -Funguje pouze pro horní tabulku s výpočtem, ne s dolní tabulkou s výsledkem
     */
    void delete_char();
};
#endif // MAINWINDOW_H
/*** Konec souboru mainwindow.h ***/
