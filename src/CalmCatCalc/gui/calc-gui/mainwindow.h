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
/*přidání matematické knihovny*/
#include "../../core/cat_calc_core.h"
/**
 * @brief Makra pro definici bloku NAMESPACE
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

private slots:
    //void calculate_clicked();
    void num();
    void del();
    void lbra();
    void rbra();
    void comma();
    void equal();
    void plus();
    void multiply();
    void minus();
    void div();
    void root();
    void sqr();
    void fact();
    void sin();
    void cos();
    void tan();
};

#endif // MAINWINDOW_H
/*** Konec souboru mainwindow.h ***/
