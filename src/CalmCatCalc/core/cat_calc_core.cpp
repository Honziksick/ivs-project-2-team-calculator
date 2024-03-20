#include "cat_calc_core.h"

using namespace std;


string calculate(string expression){
    return expression;
}

double absVal(double num){
    return num;
}

double root(int root, double num){
    return num;
}

double power(int exp, double num){
    return num;
}

double csin(double ang){
    return ang;
}

double ccos(double ang){
    return ang;
}

double ctan(double ang){
    return ang;
}

void formatCheck(string expression){
    
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
