/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          mainwindow.cpp
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
 * @file mainwindow.cpp
 * @author Lukáš Farkašovský \<xfarkal00>
 * @brief __Definice/implementace GUI nad matematickou knihovnou__
 */

/**
 * @details QT vygenerovaná část kódu
 */
#include "mainwindow.h"
#include <QKeyEvent>
#include <QWidget>
#include "./ui_mainwindow.h"
#include "../../core/cat_calc_core.cpp"

QString empty_state = "";
/*string s vysledkem*/
QString eq_str;
int comma_rate = 0;
int num_rate = 0;
int gon_rate = 0;
int err = 0;
int eq_state;

/*exception v cat_calc_core.cpp*/
std::exception e;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** @brief Převod inputu na klávesnici do kalkulačky pro čísla */

    /*nastaví text v display aby zobrazoval prazdny string*/
    ui->Display->setText(empty_state);

    /*definice tlačítek všech čísel*/
    QPushButton *num_buttons[10];

    /*for loop pro přidělení tlačítek*/
    for(int i = 0; i <= 9; ++i){
        /*v ui knihovně máme každé tlačítko pojmenované formátem B(cislo)*/
        QString button = "B" + QString::number(i);
        num_buttons[i] = MainWindow::findChild<QPushButton *>(button);

        /*propojeni tlacitek pro cisla*/
        connect(num_buttons[i], SIGNAL(pressed()), this, SLOT(num()));
    }
    /*propojeni jednotlivych tlacitek*/
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
}

MainWindow::~MainWindow(){
    delete ui;

}

void MainWindow::equal(){
    QString dis_val = ui->Display->text();
    /*prevedeni QString na string*/
    std::string dis_val_s = dis_val.toStdString();

    try {
        /*prevedeni zpatky do QString formatu*/
        QString result = QString::fromStdString(calculate(dis_val_s));      
        if(result == empty_state){
            ui->vysledek->setText("=0");
        }else{
            ui->vysledek->setText("= " + result);
            eq_str = result;
            eq_state = 1;
        }

        comma_rate = 0;
    } catch (std::invalid_argument& e) {
            /*vypise exception, ktery byl thrownut v knihovne*/
            ui->Display->setText(QString::fromStdString(e.what()));

            err = 1;
            gon_rate = 0;
        }
}

void MainWindow::del(){
    ui->Display->setText(empty_state);
    ui->vysledek->setText(empty_state);

    /*reset, aby se znovu mohla napsat carka*/
    comma_rate = 0;
    /*reset, pro spravne vyuziti gon. funkci*/
    gon_rate = 0;
    /*reset pro vypocet noveho prikladu*/
    eq_state = 0;
}


void MainWindow::delete_char(){
    QString text = ui->Display->text();
    QString new_val;
    if(err == 1){
        new_val = empty_state;
    }else{
        /*text.left vrati n znaku zleva == velikost qstringu - 1 znak*/
        new_val = text.left(text.size() - 1);
    }

    ui->Display->setText(new_val);
}

void MainWindow::num(){
    /*sender je funkce, která vrátí ukazatel na objekt, který poslal signál*/
    QPushButton *button = (QPushButton *)sender();

    num_rate++;

    QString val_button = button->text();
    QString dis_val = ui->Display->text();
    QString new_val;

    if(err == 1){
        ui->Display->setText(empty_state);
        ui->Display->setText(val_button);
        err = 0;

    }else{
        /*pokud neni nic napsano, napise jedno cislo*/
        if(dis_val == empty_state){
            ui->Display->setText(val_button);
        }else{
            /*pokud uz se jedno cislo napsalo, zacne psat dalsi za sebe*/
            new_val = dis_val + val_button;
            ui->Display->setText(new_val);
        }
    }

    /*pokud se vypsal vysledek, nove napsane cislo prepise vysledek a vypocet*/
    if(eq_state == 1){
        ui->Display->setText(val_button);
        ui->vysledek->setText(empty_state);

        eq_state = 0;
    }
}

void MainWindow::lbra(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        ui->Display->setText(val_button);
    }else{
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}

void MainWindow::rbra(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == empty_state){
        ui->Display->setText(val_button);
    }else{
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}

void MainWindow::comma(){
    /*zaruci, ze se nepouzije vicekrat*/
    comma_rate++;

    if(comma_rate == 1){
        QString val_button = ".";
        QString dis_val = ui->Display->text();
        QString new_val = dis_val + val_button;

        /*pokud neni nastavena hodnota, tak se da 0 pred carku*/
        if(dis_val == empty_state){
            new_val = "0" + val_button;
        }
        ui->Display->setText(new_val);
    }
}

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
}

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
}

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
}

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
}

void MainWindow::root(){
    QString val_button = "#";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    ui->Display->setText(new_val);
}

void MainWindow::sqr(){
    QString val_button = "^";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    ui->Display->setText(new_val);
    if(eq_state == 1){
        new_val = eq_str + val_button;
    }
    eq_state = 0;
}

void MainWindow::fact(){
    QString val_button = "!";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    ui->Display->setText(new_val);
    if(eq_state == 1){
        new_val = eq_str + val_button;
    }
    eq_state = 0;
}

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
    gon_rate++;
}

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
    gon_rate++;
}

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
    gon_rate++;
}

void MainWindow::deg_rad(){
    /*prepne deg na rad a naopak*/
    degRad = !degRad;

    /*RAD == false (default), DEG == true*/
    if(degRad == true){
        /*zmeni tlacitko, aby bylo deg nebo rad*/
        ui->Zdeg->setText("DEG");
    }else ui->Zdeg->setText("RAD");
}
/*** Konec souboru mainwindow.cpp ***/
