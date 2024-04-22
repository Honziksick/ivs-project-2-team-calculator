/*******************************************************************************
 *                                                                             *
 * Název projektu:   Calm CatCalc                                              *
 *                                                                             *
 * Soubor:           cat_calc_core_tests_for_debug.cpp                         *
 * Datum:            15.04.2024                                                *
 * Poslední změna:   22.04.2024                                                *
 *                                                                             *
 * Tým:      Calm CatCalc Coders                                               *
 *                                                                             *
 * Členové:  Farkašovský Lukáš    <xfarkal00>                                  *
 *           Hýža Pavel           <xhyzapa00>                                  *
 *           Kalina Jan           <xkalinj00>                                  *
 *           Krejčí David         <xkrejcd00>                                  *
 *        	                                                                   *
 ******************************************************************************/
/**
 * @file cat_calc_core_tests_for_debug.cpp
 * @author David Krejčí \<xkrejcd00>
 *
 * @brief Soubor obsahující několik testů matematické knihovny přímo ve funkci
 *        `main()` pro snadnější debuggování.
 * @details Testy obsažené v tomto souboru jsou převzaty ze souboru
 *          \link cat_calc_core_tests.cpp \endlink.
 * 
 * @see cat_calc_core_tests.cpp
 */

#include "cat_calc_core.h"

using namespace std;                // funkce standardní knihovny C++
using namespace catMath;            // funkce matematické knihovny 'cat_calc_core'


/**
 * @brief Testovaná přesnost kalkulačky na 14 desetinných míst
 * @see cat_calc_core_tests.cpp
*/
#define TESTED_PRECISION 0.00000000000001

/**
 * @brief Funkce porovná 2 vektory řetězců
 * @see cat_calc_core_tests.cpp
*/
bool compareVectors(vector<string> vec1, vector<string> vec2){
    if (vec1.size() != vec2.size()){
        return false;
    }
    
    for (size_t i = 0; i < vec1.size(); i++){
        if (vec1[i] != vec2[i]){
            return false;
        }
    }
    return true;
}

/**
 * @brief Hlavní funkce pro spuštění testů matematické knihovny pro debuggování.
 *
 * @details Tato funkce spustí několik testů matematické knihovny přímo ve
 *          funkci `main()` pro snadnější debuggování.
 *          Testy jsou převzaty ze souboru `cat_calc_core_tests.cpp`.
 * 
 * @see cat_calc_core_tests.cpp
 */
int main() {
    // Testovací případ pro základní výrazy.
    {
        string expression = "4";
        cout << calculate(expression) << endl;

        expression = "";
        cout << calculate(expression) << endl;

        expression = "     ";
        cout << calculate(expression) << endl;

        expression = "2!!";
        cout << calculate(expression) << endl;

        expression = "3!!";
        cout << calculate(expression) << endl;

        expression = "#4";
        cout << calculate(expression) << endl;

        expression = "(1+4)*#16";
        cout << calculate(expression) << endl;

        expression = "5+#81/2";
        cout << calculate(expression) << endl;

        expression = "3^+1";
        cout << calculate(expression) << endl;

        expression = "2*1+3^(2+1)+2";
        cout << calculate(expression) << endl;

        expression = "4 - (-8)";
        cout << calculate(expression) << endl;

        expression = "3.1+ 8.2";
        cout << calculate(expression) << endl;
    }

    // Testovací případ pro složité výrazy.
    {
        string expression = "(3.1+ 8.2) * 3 #cos(48)^2";
        cout << calculate(expression) << endl;

        expression = "sin(4!) *10";
        cout << calculate(expression) << endl;

        expression = "((sin(4!)+1) *10)+2";
        cout << calculate(expression) << endl;
    }

    // Testovací případ pro chybové stavy.
    {
        string expression = "3*8/(2-2)";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "tan(40)!";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "(-4)!";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "3*5)+4";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "2#-4";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }
    }

    // Testovací případ pro situace, které by neměly vyvolat chybu.
    {
        string expression = "3 + (-8)";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "3 - (-8)";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "89++9";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "3";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "-3";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }

        expression = "3!!";
        try {
            cout << calculate(expression) << endl;
        } catch (...) {
            cout << "Error occurred" << endl;
        }
    }

    // Testovací případ pro základní výrazy.
    {
        vector<string> result = parse("5");
        for (const auto& str : result) {
            cout << str << " ";
        }
        cout << endl;

        result = parse("5.4    +4 ! ");
        for (const auto& str : result) {
            cout << str << " ";
        }
        cout << endl;
    }

    //  Testovací případ pro parsování složitých výrazů.
    {
        vector<string> expected = {"558", "*", "0.5", "-", "(", "~", "2", ")",
                                    "+", "2", "#", "3", "^", "4"};
        vector<string> result = parse(" 558*0.5 - (-2) + 2#3^4 ");
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro základní výrazy převedené do postfixové notace.
    {
        vector<string> expected = {"5"};
        vector<string> result = postfix({"5"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;

        expected = {"5.4", "4", "!", "+"};
        result = postfix({"5.4", "+", "4", "!"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro složité výrazy převedené do postfixové notace.
    {
        vector<string> expected = {"558", "0.5", "*", "2", "~", "-",
                                     "2", "3", "4", "^", "#", "+"};
        vector<string> result = postfix({"558", "*", "0.5", "-", "(", "~",
                                        "2", ")", "+", "2", "#", "3", "^", "4"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    //  Testovací případ pro vyhodnocení základních výrazů.
    {
        string expected = "5";
        string result = evaluate({"5"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;

        expected = "29.4";
        result = evaluate({"5.4", "4", "!", "+"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro vyhodnocení složitých výrazů.
    {
        string expected = "290";
        string result = evaluate({"558", "0.5", "*", "2", "~", "-",
                                     "2", "3", "4", "^", "#", "+"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro absolutní hodnotu.
    {
        cout << (absVal(15) == 15 ? "PASS" : "FAIL") << endl;
        cout << (absVal(-15) == 15 ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro odmocninu.
    {
        cout << (root(2,25) == 5 ? "PASS" : "FAIL") << endl;
        cout << (root(12,4096) == 2 ? "PASS" : "FAIL") << endl;
        cout << (root(3,-27) == -3 ? "PASS" : "FAIL") << endl;
        cout << (abs(root(3, 2.13) - 1.286648351223739) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(root(2,3) - 1.732050807568877) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(root(4,0.023) - 0.3894322904960899) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(root(3,-0.023) + 0.284386697985156) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        double expectedResult = 11111.111060555555441;
        cout << (abs(root(2,123456789) - expectedResult) < expectedResult*TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        try {
            root(2,-16);
            cout << "FAIL" << endl;
        } catch (...) {
            cout << "PASS" << endl;
        }
    }

    // Testovací případ pro mocninu.
    {
        cout << (power(2,8) == 64 ? "PASS" : "FAIL") << endl;
        cout << (power(4,3) == 81 ? "PASS" : "FAIL") << endl;
        cout << (power(2,-4) == 16 ? "PASS" : "FAIL") << endl;
        cout << (power(3,-4) == -64 ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro sinus.
    {
        cout << (abs(csin(30) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(-30) + 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(5) - csin(365)) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(70) - 0.939692620785908) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro kosinus.
    {
        cout << (abs(ccos(60) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(-60) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(6) - ccos(366)) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(70) - 0.342020143325668) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
    }

    // Testovací případ pro tangens.
    {
        cout << (abs(ctan(45) - 1) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ctan(24) - ctan(204)) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ctan(70) - 2.747477419454622) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        try {
            ctan(270);
            cout << "FAIL" << endl;
        } catch (...) {
            cout << "PASS" << endl;
        }
    }

    // Testovací případ pro faktoriál.
    {
        size_t expectedResult = 24;
        cout << (factorial(4) == expectedResult ? "PASS" : "FAIL") << endl;
        expectedResult = 2432902008176640000;
        cout << (factorial(20) == expectedResult ? "PASS" : "FAIL") << endl;
        try {
            factorial(-5);
            cout << "FAIL" << endl;
        } catch (...) {
            cout << "PASS" << endl;
        }
    }

    // Testovací případ pro ověření, zda je znak operátorem.
    {
        string testExpression = "4 /(7+1.2)";
        bool expectedResult[] = {false,false,true,false,false,true,false,false,false,false};
        for(int i = 0; i < 10; i++){
            cout << (isOperator(testExpression[i]) == expectedResult[i] ? "PASS" : "FAIL") << endl;
        }
    }

    return 0;
}