/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           mainwindow.cpp                                            *
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
 * @file mainwindow.cpp
 * @author Lukáš Farkašovský \<xfarkal00>
 * 
 * @brief Definice funkcí využívaných v GUI nad matematickou knihovnou.
 * 
 * @details Tento zdrojový soubor obsahuje definice funkcí a metod, které jsou
 *          použity pro propojení uživatelského rozhraní aplikace s matematickou
 *          knihovnou. Zahrnuje implementace metod pro hlavní okno, dialogová
 *          okna a další prvky uživatelského rozhraní. Tyto metody zahrnují
 *          zpracování uživatelských vstupů, výpočet matematických výrazů pomocí
 *          matematické knihovny _Calm CatCalc Core_ a zobrazení výsledků.
 */

#include "mainwindow.h"
#include <QKeyEvent>
#include <QWidget>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "cat_calc_core.h"

using namespace catMath;    // funkce matematické knihovny 'cat_calc_core'


/*******************************************************************************
*                                                                              *
*                          GLOBÁLNÍ PROMĚNNÉ A FLAGY                           *
*                                                                              *
*******************************************************************************/

// Definice globálních proměnných z hlavičkového souboru 'mainwindow.h'
QString empty_state = "";
QString eq_str;
std::exception e;

// Flagy pro různé stavy
int comma_rate = 0;
int gon_rate = 0;
int err = 0;
int eq_state;


/*******************************************************************************
*                                                                              *
*                      KONSTRUKTOR A DESTRUKTOR OKNA S UI                      *
*                                                                              *
*******************************************************************************/

/* Třída reprezentující hlavní okno aplikace pro propojení signálů s tlačítky */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Nastaví text v display aby zobrazoval prazdny string
    ui->Display->setText(empty_state);

    // Definice tlačítek všech čísel
    QPushButton *num_buttons[10];

    // For loop pro přidělení tlačítek
    for(int i = 0; i <= 9; ++i){
        // V UI knihovně máme každé tlačítko pojmenované formátem B(cislo)
        QString button = "B" + QString::number(i);
        num_buttons[i] = MainWindow::findChild<QPushButton *>(button);

        // Propojení tlačíek pro čísla
        connect(num_buttons[i], SIGNAL(pressed()), this, SLOT(num()));
    }
    connect(ui->Zrovna, SIGNAL(clicked()), this, SLOT(equal()));
    connect(ui->DELETE, SIGNAL(clicked()), this, SLOT(del()));
    connect(ui->Lza, SIGNAL(clicked()), this, SLOT(lbra()));
    connect(ui->Pza, SIGNAL(clicked()), this, SLOT(rbra()));
    connect(ui->Zcarka, SIGNAL(clicked()), this, SLOT(comma()));
    connect(ui->Zplus, SIGNAL(clicked()), this, SLOT(plus()));
    connect(ui->Zkrat, SIGNAL(clicked()), this, SLOT(multiply()));
    connect(ui->Zdeleno, SIGNAL(clicked()), this, SLOT(div()));
    connect(ui->Zminus, SIGNAL(clicked()), this, SLOT(minus()));
    connect(ui->Zodmo, SIGNAL(clicked()), this, SLOT(root()));
    connect(ui->Zmoc, SIGNAL(clicked()), this, SLOT(sqr()));
    connect(ui->Zfact, SIGNAL(clicked()), this, SLOT(fact()));
    connect(ui->Zsin, SIGNAL(clicked()), this, SLOT(sin()));
    connect(ui->Zcos, SIGNAL(clicked()), this, SLOT(cos()));
    connect(ui->Ztan, SIGNAL(clicked()), this, SLOT(tan()));
    connect(ui->Zdeg, SIGNAL(clicked()), this, SLOT(deg_rad()));
    connect(ui->Zdel_ch, SIGNAL(clicked()), this, SLOT(delete_char()));
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(prompt()));


    /*                Zrušení zkratky tab pro všechny widgety                 */

    // Získáme widget centralwidget, který obsahuje tlačítka
    QObjectList buttons = ui->centralwidget->children();

    // For cyklus, který projede počtem, kolik je dětí ve widgetu
    for(QObject *obj : buttons){
        // Mění datový typ, pokud selže, přeskočí dané tlačítko
        if(QPushButton *button = qobject_cast<QPushButton*>(obj)){
            // Pokud začíná na "Z" mění ho na NoFocus
            if(button->objectName().startsWith("Z")){
                button->setFocusPolicy(Qt::NoFocus);
            }
        }
    }

    for(int i = 0; i <= 9; i++){
        num_buttons[i]->setFocusPolicy(Qt::NoFocus);
    }

    ui->Lza->setFocusPolicy(Qt::NoFocus);
    ui->Pza->setFocusPolicy(Qt::NoFocus);
    ui->DELETE->setFocusPolicy(Qt::NoFocus);
    ui->Display->setFocusPolicy(Qt::NoFocus);
    ui->vysledek->setFocusPolicy(Qt::NoFocus);

} // konec konstruktoru


/*                        Destruktor třídy MainWindow                         */
MainWindow::~MainWindow(){
    delete ui;

}

/*******************************************************************************
*                                                                              *
*                         PROPOJENÍ SIGNÁLŮ S TLAČÍTKY                         *
*                                                                              *
*******************************************************************************/

/*     Slot pro zpracování signálu vypsání výsledku po vyhodnocení výrazu     */
void MainWindow::equal(){
    QString dis_val = ui->Display->text();
    // Převedení QString na string
    std::string dis_val_s = dis_val.toStdString();

    try{
        // Převedení zpátky do QString formátu
        QString result = QString::fromStdString(calculate(dis_val_s));
        if(result == empty_state){
            ui->vysledek->setText("= 0");
            eq_state = 1;
        }
        else{
            ui->vysledek->setText("= " + result);
            eq_str = result;
            eq_state = 1;
        }
        
    }catch (std::invalid_argument& e){
        // Vypíše exception, který byl thrownut v knihovně
        ui->Display->setText(QString::fromStdString(e.what()));

        err = 1;
        gon_rate = 0;
    }
}


/*             Slot pro zpracování signálu smazání celého výrazu              */
void MainWindow::del(){
    ui->Display->setText(empty_state);
    ui->vysledek->setText(empty_state);

    // Reset, aby se znovu mohla napsat čárka
    comma_rate = 0;
    // Reset, pro správné využití gon. funkci
    gon_rate = 0;
    // Reset pro výpočet nového příkladu
    eq_state = 0;
}


/*            Slot pro zpracování signálu smazání posledního znaku            */
void MainWindow::delete_char(){
    QString text = ui->Display->text();
    QString new_val;
    if(err == 1){
        new_val = empty_state;
    }
    else {
        if(text.endsWith("n") || text.endsWith("s")){
            // Zaručí, že tan, cos a sin se smaže celé
            new_val = text.left(text.size() - 3);
            }
        else{
            // text.left vrátí n znaku zleva == velikost qstringu - 1 znak
            new_val = text.left(text.size() - 1);
            }
        }

    ui->Display->setText(new_val);
}


/*                     Slot pro zpracování signálu čísel                      */
void MainWindow::num(){
    // 'sender()' je funkce, která vrátí ukazatel na objekt, který poslal signál
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();
    QString new_val;

    if(err == 1){
        ui->Display->setText(empty_state);
        ui->Display->setText(val_button);
        err = 0;

    }
    else{
        // Pokud není nic napsáno, napíše jedno číslo
        if(dis_val == empty_state){
            ui->Display->setText(val_button);
        }
        else{
            // Pokud už se jedno číslo napsalo, začne psát další za sebe
            new_val = dis_val + val_button;
            ui->Display->setText(new_val);
        }
    }

    // Pokud se vypsal výsledek, nově napsané číslo přepíše výsledek a výpočet
    if(eq_state == 1){
        ui->Display->setText(val_button);
        ui->vysledek->setText(empty_state);

        eq_state = 0;
    }
}


/*              Slot pro zpracování signálu vypsání levé závorky              */
void MainWindow::lbra(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        ui->Display->setText(val_button);
    }
    else{
        QString new_val = dis_val + val_button;
        
        if(eq_state == 1){
            new_val = eq_str + val_button;
        }

        ui->Display->setText(new_val);
        eq_state = 0;
    }
}


/*             Slot pro zpracování signálu vypsání pravé závorky              */
void MainWindow::rbra(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        ui->Display->setText(val_button);
    }
    else{
        QString new_val = dis_val + val_button;

        if(eq_state == 1){
            new_val = eq_str + val_button;
        }
        ui->Display->setText(new_val);
        eq_state = 0;
    }
}


/*                 Slot pro zpracování signálu vypsání čárky                  */
void MainWindow::comma(){
    // Zaručí, že se nepoužije vícekrát
    comma_rate++;

    if(comma_rate == 1){
        QString val_button = ".";
        QString dis_val = ui->Display->text();
        QString new_val = dis_val + val_button;

        // Pokud není nastavena hodnota nebo bylo pressnuto =, tak se dá 0 před čárku
        if(dis_val == empty_state || eq_state == 1){
            new_val = "0" + val_button;
        }

        ui->Display->setText(new_val);
        eq_state =0;
    }
}


/*           Slot pro zpracování signálu vypsání operátoru sčítání            */
void MainWindow::plus(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == empty_state){
        new_val = "0" + val_button;
    }

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    comma_rate = 0;
    eq_state = 0;
    gon_rate = 1;
}


/*          Slot pro zpracování signálu vypsání operátoru odsčítání           */
void MainWindow::minus(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == empty_state){
        new_val = "0" + val_button;
    }

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    comma_rate = 0;
    eq_state = 0;
    gon_rate = 1;
}


/*           Slot pro zpracování signálu vypsání operátoru násobení           */
void MainWindow::multiply(){
    QString val_button = "*";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == empty_state){
        new_val = "0" + val_button;
    }

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    comma_rate = 0;
    eq_state = 0;
    gon_rate = 1;
}


/*            Slot pro zpracování signálu vypsání operátoru dělení            */
void MainWindow::div(){
    QString val_button = "/";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == empty_state){
        new_val = "0" + val_button;
    }

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    comma_rate = 0;
    eq_state = 0;
    gon_rate = 1;
}


/*           Slot pro zpracování signálu vypsání operátoru mocniny            */
void MainWindow::root(){
    QString val_button = "#";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    ui->Display->setText(new_val);
}


/*          Slot pro zpracování signálu vypsání operátoru odmocniny           */
void MainWindow::sqr(){
    QString val_button = "^";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    eq_state = 0;
}


/*          Slot pro zpracování signálu vypsání operátoru faktoriálu          */
void MainWindow::fact(){
    QString val_button = "!";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(eq_state == 1){
        new_val = eq_str + val_button;
    }

    ui->Display->setText(new_val);
    eq_state = 0;
}


/*             Slot pro zpracování signálu vypsání operátoru sinu             */
void MainWindow::sin(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        dis_val = "0";
    }

    QString new_val = val_button + "(" + dis_val + ")";

    if(gon_rate > 0){
        new_val = dis_val + val_button;
    }

    ui->Display->setText(new_val);

    if(eq_state == 1){
        ui->Display->setText(val_button + "(" + eq_str + ")");
        ui->vysledek->setText(empty_state);

        eq_state = 0;
    }

    gon_rate++;
}


/*           Slot pro zpracování signálu vypsání operátoru tangensu           */
void MainWindow::tan(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        dis_val = "0";
    }

    QString new_val = val_button + "(" + dis_val + ")";

    if(gon_rate > 0){
        new_val = dis_val + val_button;
    }

    ui->Display->setText(new_val);

    if(eq_state == 1){
        ui->Display->setText(val_button + "(" + eq_str + ")");
        ui->vysledek->setText(empty_state);

        eq_state = 0;
    }
    
    gon_rate++;
}


/*            Slot pro zpracování signálu vypsání operátoru kosinu            */
void MainWindow::cos(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        dis_val = "0";
    }

    QString new_val = val_button + "(" + dis_val + ")";

    if(gon_rate > 0){
        new_val = dis_val + val_button;
    }

    ui->Display->setText(new_val);

    if(eq_state == 1){
        ui->Display->setText(val_button + "(" + eq_str + ")");
        ui->vysledek->setText(empty_state);

        eq_state = 0;
    }

    gon_rate++;
}


/*    Slot pro zpracování signálu převedení ze stupňů na radiány a naopak     */
void MainWindow::deg_rad(){
    // Přepne stupně na radiány a naopak
    degRad = !degRad;

    // RAD == false (default), DEG == true
    if(degRad == true){
        // Změní tlačítko, aby bylo deg nebo rad
        ui->Zdeg->setText("DEG");
    }
    else ui->Zdeg->setText("RAD");
}

void MainWindow::prompt(){

    const char *msg = 
"Základní vlastnosti kalkulačky:\n"
"1) Kalkulačka Calm CatCalc™ je jednořádkový model kalkulačky, proto se tak i operuje.\n"
"2) Dané tlačítka aplikace vykonávají operace, které by dělalo i počítací zařízení.\n"
"3) Tlačítko DEL slouží k smazání celého výrazu a tlačítko se značkou zpětné šipky "
"naopak maže po jednom.\n"
"4) Při počítání může dojít k chybě syntaktické (Syntax Error), matematické (Math Error)"
" a chybě závorek (Parenthesis Mismatch)\n"
" - 'Syntax Error' značí chybu logiky zadané uživatelem (např. výraz *-+)\n"
" - 'Math Error' značí chybu matematické logiky zadané uživatelem (např. dělení nulou)\n"
" - 'Parenthesis Error' značí chybu uzavření závorkami "
"(např. vynechání uzavírací závorky)\n"
"Podrobnější návod naleznete v uživatelské příručce\n\n"

"Klávesové zkratky: \n"

"Tlačítka s čísly reprezentují jednotlivé klávesy.\n"
"Tlačítko '=' má zkratku pravého 'Enteru'\n"
"Tlačítka se závorkami a čárkou ',' také jsou reprezentovány jednotlivými klávesami.\n"
"Tlačítka pro operace '+ - * /' jsou reprezentovány jednotlivými klávesami.\n"
"Tlačítko DEL má zkratku 'Del' a tlačítko '<=' má zkratku 'Backspace'\n"
"Tlačítko RAD má zkratku 'D'\n"
"Tlačítko sin má zkratku 'S'\n"
"Tlačítko cos má zkratku 'C'\n"
"Tlačítko tan má zkratku 'T'\n"
"Tlačítko faktoriálu má zkratku '!'\n"
"Tlačítko odmocniny má zkratku 'R'\n"
"Tlačítko mocniny má zkratku 'E'\n";

    QMessageBox::information(this, "Nápověda", msg);
}

/*** Konec souboru mainwindow.cpp ***/
