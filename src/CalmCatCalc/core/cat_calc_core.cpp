#include "cat_calc_core.h"

using namespace std;

/**
 *  Globání proměnná určující, jestli jsou hodnoty zadány ve stupních nebo radiánech
 *  false = stupně
 *  true = radiány
 */
bool degRad = false;

string calculate(string expression){
    return expression;
}

double absVal(double num){
    if(num >= 0){
        return num;
    }
    return -num;
}

size_t factorial(size_t num){
    size_t result = 1;
    while(num > 1){
        if(__SIZE_MAX__ / result < num){
            throw overflow_error("Overflow");
        }
        result = result * num;
        num--;
    }
    return result;
}

double root(int root, double num){

    if(num < 0 && root%2 == 0){
        throw invalid_argument("MathError");
    }
    if(num == 0 || num == 1 || num == -1){
        return num;
    }

    double minVal, maxVal;
    if(num > 0 && num < 1){
        minVal = num;
        maxVal = 1;
    }else if(num > -1 && num < 0){
        minVal = -1;
        maxVal = num;
    }else if(num > 1){
        minVal = 1;
        maxVal = num;
    }else{
        minVal = num;
        maxVal = -1;
    }

    int numOfCycles = 0;
    double estimate = (minVal + maxVal)/2;
    while((absVal(absVal(power(root,estimate)) - absVal(num)) > CALC_PRECISION) && (numOfCycles < MAX_CYCLES)){
        if(power(root,estimate) > num){
            maxVal = estimate;
        }else{
            minVal = estimate;
        }
        estimate = (minVal + maxVal)/2;
        numOfCycles++;
    }
    return estimate;
}

double power(int exp, double num){
    if(exp < 0){
        if(num == 0){
            throw invalid_argument("MathError");
        }else{
            double result = 1/power(-exp, num);
            return result;
        }
    }else{
        double result = 1;
        for(int i = 0; i < exp; i++){
            result = result * num;
        }
        return result;
    }
}

/**
 * @details Převede úhel do radiánů, pokud potřeba a upraví jej na rozmezí 0 - 2PI
*/
double normalizeAngle(double ang){
    if(degRad == false){
        ang = ang *(PI/180);
    }

    while(ang < 0){
        ang = ang + 2*PI;
    }
    while(ang > 2*PI){
        ang = ang - 2*PI;
    }
    return ang;
}

double csin(double ang){
    ang = normalizeAngle(ang);
    
    double result = 0;
    double term = ang;
    int i = 1;
    while (absVal(term) >= CALC_PRECISION && i < MAX_CYCLES) {
        result += term;
        term = -term * ang * ang / ((2 * i) * (2 * i + 1));
        i++;
    }
    return result;
}

double ccos(double ang){
    ang = normalizeAngle(ang);

    double result = 0;
    double term = 1;
    int i = 1;
    while (absVal(term) >= CALC_PRECISION && i < MAX_CYCLES) {
        result += term;
        term = -term * ang * ang / ((2 * i - 1) * (2 * i));
        i++;
    }
    return result;
}

double ctan(double ang){
    // Pokud je zadaný úhel nedefinovaný pro tangens
    if(absVal(normalizeAngle(ang) - PI/2) < CALC_PRECISION ||
     absVal(normalizeAngle(ang) - 3*PI/2) < CALC_PRECISION)
    {
        throw invalid_argument("MathError");
    }
    double result = csin(ang)/ccos(ang);
    return result;
}

void formatCheck(string expression){
    // Jen blbost, aby šlo přeložit
    if(!expression.empty()){
       throw overflow_error("");
    }
}

vector<string> parse(string expression){
    vector<string> result;
    result.push_back(expression);
    return result;
}

vector<string> postfix(vector<string> parsedExpression){
    return parsedExpression;
}

string evaluate(vector<string> postfixExpression){
    return postfixExpression.front();
}

/*** Konec souboru cat_calc_core.cpp ***/
