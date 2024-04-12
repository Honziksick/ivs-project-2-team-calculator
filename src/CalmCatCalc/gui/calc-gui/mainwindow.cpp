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
#include "../../core/cat_calc_core.h"
#include "../../core/cat_calc_core.cpp"


/**/

QString calcVal = "";
int comma_rate = 0;
int rbra_rate = 0;
int lbra_rate = 0;
int num_rate = 0;
int mult_rate = 0;
int err = 0;

/*exception v cat_calc_core.cpp*/
std::exception e;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** @brief Převod inputu na klávesnici do kalkulačky pro čísla */

    /*nastaví text v display aby zobrazoval prazdny string*/
    ui->Display->setText(calcVal);

    /*definice tlačítek všech čísel*/
    QPushButton *num_buttons[10];

    /*for loop pro přidělení tlačítek*/
    for(int i = 0; i <= 9; ++i){
        /*v ui knihovně máme každé tlačítko pojmenované formátem B(cislo)*/
        QString button = "B" + QString::number(i);
        num_buttons[i] = MainWindow::findChild<QPushButton *>(button);

        /*propojeni tlacitek*/
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
        if(result == ""){
            ui->Display->setText(calcVal);
        }else{
            ui->Display->setText(result);
        }

        comma_rate = 0;
    } catch (std::invalid_argument& e) {
            /*vypise exception, ktery byl thrownut v knihovne*/
            ui->Display->setText(QString::fromStdString(e.what()));

            err = 1;
            printf("%d", err);
        }
}

void MainWindow::del(){

    ui->Display->setText(calcVal);

    /*reset, aby se znovu mohla napsat carka*/
    comma_rate = 0;
}

void MainWindow::num(){
    /*sender je funkce, která vrátí ukazatel na objekt, který poslal signál*/
    QPushButton *button = (QPushButton *)sender();

    num_rate++;

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(err == 1){
        ui->Display->setText("");
        ui->Display->setText(val_button);
        err = 0;

    }else{
        /*pokud neni nic napsano, napise jedno cislo*/
        if(dis_val == ""){
            ui->Display->setText(val_button);
        }else{
            /*pokud uz se jedno cislo napsalo, zacne psat dalsi za sebe*/
            QString new_val = dis_val + val_button;
            ui->Display->setText(new_val);
        }
    }
}

void MainWindow::lbra(){
    QPushButton *button = (QPushButton *)sender();

    lbra_rate++;

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == ""){
        ui->Display->setText(val_button);
    }else{
        QString new_val = dis_val + val_button;
        ui->Display->setText(new_val);
    }
}

void MainWindow::rbra(){
    QPushButton *button = (QPushButton *)sender();

    rbra_rate++;

    QString val_button = button->text();
    QString dis_val = ui->Display->text();

    if(dis_val == ""){
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
        if(dis_val == ""){
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

    if(dis_val == ""){
        new_val = "0" + val_button;
    }
    ui->Display->setText(new_val);

}

void MainWindow::minus(){
    QPushButton *button = (QPushButton *)sender();

    QString val_button = button->text();
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == ""){
        new_val = "0" + val_button;
    }
    ui->Display->setText(new_val);

}

void MainWindow::multiply(){
    QString val_button = "*";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == ""){
        new_val = "0" + val_button;
    }
    ui->Display->setText(new_val);

}

void MainWindow::div(){
    QString val_button = "/";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    if(dis_val == ""){
        new_val = "0" + val_button;
    }
    ui->Display->setText(new_val);

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

}

void MainWindow::fact(){
    QString val_button = "!";
    QString dis_val = ui->Display->text();
    QString new_val = dis_val + val_button;

    ui->Display->setText(new_val);
}

/*** Konec souboru mainwindow.cpp ***/
