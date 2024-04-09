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
#include "./ui_mainwindow.h"

string calcVal = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** @brief Převod inputu na klávesnici do kalkulačky pro čísla */

    /*nastaví text v display aby zobrazoval prazdny string*/
    ui->Display->setText(QString::fromStdString(calcVal));

    /*definice tlačítek všech čísel*/
    QPushButton *num_buttons[10];

    /*for loop pro přidělení tlačítek*/
    for(int i = 0; i <= 9; ++i){
        /*v ui knihovně máme každé tlačítko pojmenované formátem B(cislo)*/
        QString button = "B" + QString::number(i);
        num_buttons[i] = MainWindow::findChild<QPushButton *>(button);

        /*propojeni tlacitek*/
        connect(num_buttons[i], SIGNAL(clicked()), this, SLOT(num_pressed()));
    }

    connect(ui->DELETE, SIGNAL(clicked()), this, SLOT(del()));
    connect(ui->Lza, SIGNAL(clicked()), this, SLOT(lza()));
    connect(ui->Pza, SIGNAL(clicked()), this, SLOT(pza()));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::del(){

    ui->Display->setText("");
}

void MainWindow::num_pressed(){
    /*sender je funkce, která vrátí ukazatel na objekt, který poslal signál*/
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    /*pokud neni nic napsano, napise jedno cislo*/
    if(dis_val == ""){
        ui->Display->setText(val_button);
    }else{
        /*pokud uz se jedno cislo napsalo, zacne psat dalsi za sebe*/
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}

void MainWindow::lza(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == ""){
        ui->Display->setText(val_button);
    }else{
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}

void MainWindow::pza(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == ""){
        ui->Display->setText(val_button);
    }else{
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}
/*** Konec souboru mainwindow.cpp ***/
