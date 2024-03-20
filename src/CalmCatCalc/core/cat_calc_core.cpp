#include "cat_calc_core.h"

using namespace std;


string calculate(string expression){
    return expression;
}

double absVal(double num){
    if(num >= 0){
        return num;
    }
    return -num;
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

    double eps = 0.000000000000001;
    double estimate = (minVal + maxVal)/2;
    while((absVal(absVal(power(root,estimate)) - absVal(num)) > eps)){
        if(power(root,estimate) > num){
            maxVal = estimate;
        }else{
            minVal = estimate;
        }
        estimate = (minVal + maxVal)/2;
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
