/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          cat_calc_core.h
 * Datum:           19.03.2024
 * Poslední změna:  27.03.2024
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
 * @file cat_calc_core.cpp
 * @author David Krejčí \<xkrejcd00>
 * @brief __Definice/implementace funkcí matematické knihovny Calm CatCalc Core.__
 * @details _Tento soubor obsahuje implementace funkcí, které jsou definovány
 * v matematické knihovně Calm CatCalc Core (souboru cat_calc_core.h)._
 */

#include "cat_calc_core.h"

using namespace std;

bool degRad = false;

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
        throw invalid_argument("Math error");
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
            throw invalid_argument("Math error");
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
        throw invalid_argument("Math error");
    }
    double result = csin(ang)/ccos(ang);
    return result;
}

bool isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
        c == '#' || c == '!' || c == 's' || c == 'c' || c == 't' || c == '~')
    {
        return true;
    }
    else{
        return false;
    }
}

vector<string> parse(string expression){
    vector<string> result;
    string token = "";
    // true, pokud poslední token byl operand nebo "("
    bool lastOp = true;
    
    for(char c : expression){
        if(isspace(c)){
            if(token.length() > 0){
                result.push_back(token);
                token.clear();
            }
        }else if(isOperator(c) || c == '(' || c == ')'){
            if(token.length() > 0){
                result.push_back(token);
                token.clear();
            }
            if(c == '-' && lastOp){
                result.push_back("~");
            }else if(c == '+' && lastOp){
                //Unární + nic nemění, může se zahodit
            }else{
                result.push_back(string(1,c));
            }
            if(c == ')'){
                lastOp = false;
            }else{
                lastOp = true;
            }
        }else{
            token.append(string(1,c));
            lastOp = false;
        }
    }

    if(token.length() > 0){
        result.push_back(token);
    }

    return result;
}

int priority(string op){
    if(op == "(" || op == ")"){
        return 0;
    }else if(op == "+" || op == "-"){
        return 1;
    }else if(op == "*" || op == "/"){
        return 2;
    }else if(op == "~"){
        return 5;
    }else if(op == "s" || op == "c" || op == "t"){
        return 4;
    }else{
        return 3;
    }
}

bool associativity(string op){
    if(op == "+" || op == "-" || op == "*" || op == "/" || op == "(" || op == ")"){
        return true; // Left
    }else{
        return false; // Right
    }
}

vector<string> postfix(vector<string> parsedExpression){
    vector<string> postfixExpression;
    vector<string> stack;

    for(string token : parsedExpression){

        if(isdigit(token[0])){
            postfixExpression.push_back(token);

        }else if(token == "("){
            stack.push_back(token);

        }else if(token == ")"){
            while(stack.back() != "("){
                if(stack.size() == 0){
                    throw invalid_argument("Parenthesis mismatch");
                }else{
                    postfixExpression.push_back(stack.back());
                    stack.pop_back();
                }
            }
            stack.pop_back();

        }else{
            if(stack.size() == 0){
                stack.push_back(token);
            }else if(priority(token) > priority(stack.back()) ||
                    (priority(token) == priority(stack.back()) && associativity(token) == false))
            {
                stack.push_back(token);
            }else{
                while(priority(token) < priority(stack.back()) ||
                    (priority(token) == priority(stack.back()) && associativity(token) == true))
                {
                    postfixExpression.push_back(stack.back());
                    stack.pop_back();
                    if(stack.size() == 0){
                        break;
                    }
                }
                stack.push_back(token);
            }
        }
    }
    while(stack.size() > 0){
        postfixExpression.push_back(stack.back());
        stack.pop_back();
    }

    return postfixExpression;
}

string doubleToString(double x){
    size_t numLen = 0;
    size_t i = 10;
    while(x/i > 1){
        numLen++;
        i = i*10;
    }

    ostringstream stream;
    stream << fixed << setprecision(16-numLen) << x;
    string result = stream.str();
    size_t dotIdx = result.find('.');
    if(dotIdx != string::npos){
        size_t notZeroIdx = result.find_last_not_of('0');
        if(notZeroIdx <= dotIdx){
            result.erase(dotIdx);
        }else if(notZeroIdx < result.size()-1){
            result.erase(notZeroIdx+1);
        }
    }
    size_t nineIdx = result.find_last_of('9');
    if(nineIdx == string::npos){
        return result;
    }
    if(nineIdx >= result.size()-3 && (dotIdx == string::npos || dotIdx < nineIdx)){
        result.erase(nineIdx);
        while(result.back() == '9'){
            result.erase(result.size()-1);
            if(result.back() == '.'){
                result.erase(result.size()-1);
                break;
            }
        }
        size_t inc = result.find_last_not_of('9');
        if(inc == string::npos){
            string tmp = "";
            tmp.push_back('1');
            for(int i = result.size(); i > 0; i--){
                tmp.push_back('0');
            }
            result = tmp;
            return result;
        }
        result[inc] = result[inc]+1;
    }
    return result;
}




string evalAdd(string num1, string num2){
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x+y);
    }else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x+y);
    }
}

string evalSub(string num1, string num2){
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x-y);
    }else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x-y);
    }
}

string evalMul(string num1, string num2){
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x*y);
    }else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x*y);
    }
}

string evalDiv(string num1, string num2){
    if(num2 == "0"){
        throw invalid_argument("Math error");
    }
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x/y);
    }else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        if(x%y > 0){
            double x = stod(num1);
            double y = stod(num2);
            return doubleToString(x/y);
        }
        return to_string(x/y);
    }
}

string evalNeg(string num1){
    if(num1.find('.') != string::npos){
        double x = stod(num1);
        return doubleToString(-x);
    }else{
        long long x = stoll(num1);
        return to_string(-x);
    }
}





string evaluateOperation(char op, vector<string> *stack){
    string xs;
    string ys;
    double xd;
    size_t z;
    int exp;
    switch(op){
        case '+':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            xs = stack->back();
            stack->pop_back();
            ys = stack->back();
            stack->pop_back();
            return evalAdd(xs,ys);
        case '-':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            xs = stack->back();
            stack->pop_back();
            ys = stack->back();
            stack->pop_back();
            return evalSub(ys,xs);
        case '*':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            xs = stack->back();
            stack->pop_back();
            ys = stack->back();
            stack->pop_back();
            return evalMul(xs,ys);
        case '/':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            xs = stack->back();
            stack->pop_back();
            ys = stack->back();
            stack->pop_back();
            return evalDiv(ys,xs);
        case '~':
            if(stack->size() < 1){
                throw invalid_argument("Syntax error");
            }
            xs = stack->back();
            stack->pop_back();
            return evalNeg(xs);
        case '^':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            for(char c : stack->back()){
                if(c == '.'){
                    throw invalid_argument("Math error");
                }
            }

            exp = stoi(stack->back());
            stack->pop_back();
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(power(exp,xd));
        case '#':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            xd = stod(stack->back());
            stack->pop_back();
            for(char c : stack->back()){
                if(c == '.'){
                    throw invalid_argument("Math error");
                }
            }
            exp = stoi(stack->back());
            stack->pop_back();
            return doubleToString(root(exp,xd));
        case '!':
            if(stack->size() < 1){
                throw invalid_argument("Syntax error");
            }
            if(stack->back().find_first_of('-') != string::npos){
                throw invalid_argument("Math error");
            }
            for(char c : stack->back()){
                if(c == '.'){
                    throw invalid_argument("Math error");
                }
            }
            z = stoul(stack->back());
            stack->pop_back();
            return to_string(factorial(z));
        case 's':
            if(stack->size() < 1){
                throw invalid_argument("Syntax error");
            }
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(csin(xd));
        case 'c':
            if(stack->size() < 1){
                throw invalid_argument("Syntax error");
            }
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(ccos(xd));
        case 't':
            if(stack->size() < 1){
                throw invalid_argument("Syntax error");
            }
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(ctan(xd));
        
        default :
            throw invalid_argument("Syntax error");
    }
}

string evaluate(vector<string> postfixExpression){

    while(postfixExpression.size() > 1){
        vector<string> stack;
        bool flag = false;
        for(string token : postfixExpression){
            if(token.length() == 1 && isOperator(token[0]) && flag == false){
                string result = evaluateOperation(token[0], &stack);
                stack.push_back(result);
                flag = true;
            }else{
                stack.push_back(token);
            }
        }
        postfixExpression = stack;
    }
    return postfixExpression.front();
}

string calculate(string expression){
    bool noNum = true;
    for(char c : expression){
        if(isdigit(c)){
            noNum = false;
            break;
        }
    }
    if(noNum == true){
        return "0";
    }

    size_t idx = expression.find("sin");
    while (idx != string::npos) {
        expression.replace(idx, 3, "s");
        idx = expression.find("sin");
    }
    idx = expression.find("cos");
    while (idx != string::npos) {
        expression.replace(idx, 3, "c");
        idx = expression.find("cos");
    }
    idx = expression.find("tan");
    while (idx != string::npos) {
        expression.replace(idx, 3, "t");
        idx = expression.find("tan");
    }
    vector<string> tokens = parse(expression);
    tokens = postfix(tokens);
    return evaluate(tokens);
}

/*** Konec souboru cat_calc_core.cpp ***/
