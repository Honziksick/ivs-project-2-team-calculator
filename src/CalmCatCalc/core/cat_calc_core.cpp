/** @cond */
/*
 * Název projektu:  Calm CatCalc
 *
 * Soubor:          cat_calc_core.h
 * Datum:           19.03.2024
 * Poslední změna:  16.04.2024
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

// Globální proměnná určující, jestli jsou hodnoty zadány ve stupních nebo radiánech
// FALSE = stupně, TRUE = radiány
bool degRad = true;

double absVal(double num){
    if(num >= 0){
        return num;
    }
    return -num;
}

size_t factorial(size_t num){
    size_t result = 1;
    while(num > 1){
        // Kontrola přetečení
        if(__SIZE_MAX__ / result < num){
            throw overflow_error("Overflow");
        }
        result = result * num;
        num--;
    }
    return result;
}

double root(int exp, double num){
    // Kontrola vstupních hodnot pro záporný základ
    if(num < 0 && exp%2 == 0){
        throw invalid_argument("Math error");
    }
    // Kontrola vstupních hodnot pro záporný exponent
    if(exp < 0){
        if(num == 0){
            throw invalid_argument("Math error");
        }
        else{
            // Pokud je základ záporný, tak se funkce zavolá s opačným exponentem
            double result = 1/root(-exp, num);
            return result;
        }
    }

    // Pro 0,1,-1 je výsledek roven základu
    if(num == 0 || num == 1 || num == -1){
        return num;
    }

    double minVal, maxVal; // Minimální a maximální hodnota pro binární vyhledávání
    // Rozdělení výsledku na interval
    if(num > 0 && num < 1){
        minVal = num;
        maxVal = 1; 
    }
    else if(num > -1 && num < 0){
        minVal = -1;
        maxVal = num;
    }
    else if(num > 1){
        minVal = 1;
        maxVal = num;
    }
    else{
        minVal = num;
        maxVal = -1;
    }

    int numOfCycles = 0;
    double estimate = (minVal + maxVal)/2; // Odhad výsledku
    // Binární vyhledávání
    // Ukončí se, pokud je rozdíl mezi odhadem a skutečným výsledkem menší než přesnost
    // Nebo pokud je počet cyklů větší než maximální počet cyklů
    while((absVal(absVal(power(exp,estimate)) - absVal(num)) > CALC_PRECISION) && (numOfCycles < MAX_CYCLES)){
        // Pokud je výsledek moc velký, tak se sníží horní mez
        if(power(exp,estimate) > num){
            maxVal = estimate;
        // Pokud je výsledek moc malý, tak se zvýší dolní mez
        }
        else{
            minVal = estimate;
        }
        estimate = (minVal + maxVal)/2;
        numOfCycles++;
    }
    return estimate;
}

double power(int exp, double num){
    // Kontrola vstupních hodnot pro záporný exponent
    if(exp < 0){
        if(num == 0){
            throw invalid_argument("Math error");
        }
        else{
            // Pokud je exponent záporný, tak se funkce zavolá s opačným exponentem
            double result = 1/power(-exp, num);
            return result;
        }
    }
    else{
        double result = 1;
        // Výpočet mocniny
        for(int i = 0; i < exp; i++){
            result = result * num;
        }
        return result;
    }
}

double normalizeAngle(double ang){
    // Pokud je úhel ve stupních, tak se převede na radiány
    if(degRad == false){
        ang = ang *(PI/180);
    }

    // Úprava úhlu na interval 0 - 2PI
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
    int i = 1;  //Počet cyklů
    // Dokuď je hodnota členu větší než přesnost nebo není dosaženo maximálního počtu cyklů
    while ( (absVal(term)>=CALC_PRECISION) && (i<MAX_CYCLES) ){
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
    int i = 1;  //Počet cyklů
    // Dokuď je hodnota členu větší než přesnost nebo není dosaženo maximálního počtu cyklů
    while ( (absVal(term)>=CALC_PRECISION) && (i<MAX_CYCLES) ){
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
    
    // Cyklus procházející všechny znaky ve vstupním řetězci
    for(char c : expression){
        // Pokud je znak mezera, tak se token přidá do výsledku
        if(isspace(c)){
            if(token.length() > 0){
                result.push_back(token);
                token.clear();
            }
        }
        // Pokud je znak operátor nebo závorka
        else if(isOperator(c) || c == '(' || c == ')'){
            // Pokud token není prázdný, tak se přidá do výsledku
            if(token.length() > 0){
                result.push_back(token);
                token.clear();
            }
            // Pokud před '-' byl operátor nebo '(', tak se změní na unární mínus
            if(c == '-' && lastOp){
                result.push_back("~");
            }
            //Unární + nic nemění, může se zahodit
            else if(c == '+' && lastOp){
                continue;
            }
            // Jinak se operátor přidá do výsledku
            else{
                result.push_back(string(1,c));
            }
            if(c == ')'){
                lastOp = false;
            }
            else{
                lastOp = true;
            }
        }
        // Pokud je načtený znak číslice, tak se přidá do tokenu
        else{
            token.append(string(1,c));
            lastOp = false;
        }
    }
    // Pokud je ještě nějaký token, tak se přidá do výsledku
    if(token.length() > 0){
        result.push_back(token);
    }

    return result;
}

int priority(string op){
    if(op == "(" || op == ")"){
        return 0;
    }
    else if(op == "+" || op == "-"){
        return 1;
    }
    else if(op == "*" || op == "/"){
        return 2;
    }
    else if(op == "~"){
        return 5;
    }
    else if(op == "s" || op == "c" || op == "t"){
        return 4;
    }
    else{
        return 3;
    }
}

bool associativity(string op){
    if(op == "+" || op == "-" || op == "*" || op == "/" || op == "(" || op == ")"){
        return true; // Left
    }
    else{
        return false; // Right
    }
}

vector<string> postfix(vector<string> parsedExpression){
    vector<string> postfixExpression;
    vector<string> stack;

    // Cyklus procházející všechny tokeny v infixovém výrazu
    for(string token : parsedExpression){
        // Pokud je token číslo, tak se přidá do výsledku
        if(isdigit(token[0])){
            postfixExpression.push_back(token);

        }
        // Otevřená závorka se přidá do zásobníku
        else if(token == "("){
            stack.push_back(token);

        }
        // Uravření závorky znamená, že se provedou všechny operace mezi závorkami
        else if(token == ")"){
            while(stack.back() != "("){
                // Pokud se nenašel začátek závorky, tak se vyhodí výjimka
                if(stack.size() == 0){
                    // Nemělo by se nikdy stát, protože se kontroluje při formatování
                    throw invalid_argument("Parenthesis mismatch");
                }
                else{
                    postfixExpression.push_back(stack.back());
                    stack.pop_back();
                }
            }
            // Otevřená závorka se odstraní ze zásobníku
            stack.pop_back();

        }
        // Pokud je token operátor
        else{
            // Pokud je zásobník prázdný, tak se operátor přidá do zásobníku
            if(stack.size() == 0){
                stack.push_back(token);
            }
            // Pokud je priorita operátoru větší než priorita operátoru na vrcholu zásobníku
            // nebo je stejná priorita a operátor je pravou asociativitou
            // přidá se operátor do zásobníku
            else if( (priority(token) > priority(stack.back())) ||
                (priority(token) == priority(stack.back()) && associativity(token) == false) )
            {
                stack.push_back(token);
            }
            // Jinak se provedou operace ze zásobníku s větší prioritou
            // nebo stejnou prioritou a levou asociativitou
            else{
                while( (priority(token) < priority(stack.back())) ||
                    (priority(token)==priority(stack.back()) && associativity(token)==true) )
                {
                    postfixExpression.push_back(stack.back());
                    stack.pop_back();
                    if(stack.size() == 0){
                        break;
                    }
                }
                // Nakonec se načtený operátor přidá do zásobníku
                stack.push_back(token);
            }
        }
    }
    // Všechny zbývající operátory ze zásobníku se přidají do výsledku
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
        }
        else if(notZeroIdx < result.size()-1){
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
        if(result[inc] == '.'){
            result.erase(inc);
        }
        else{
            result[inc] = result[inc]+1;
        }
    }
    return result;
}

string evalAdd(string num1, string num2){
    // Pokud je některý z operandů desetinné číslo, tak se provede operace s double
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x+y);
    }
    // Jinak se provede operace s long long
    else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x+y);
    }
}

string evalSub(string num1, string num2){
    // Pokud je některý z operandů desetinné číslo, tak se provede operace s double
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x-y);
    }
    // Jinak se provede operace s long long
    else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x-y);
    }
}

string evalMul(string num1, string num2){
    // Pokud je některý z operandů desetinné číslo, tak se provede operace s double
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x*y);
    }
    // Jinak se provede operace s long long
    else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        return to_string(x*y);
    }
}

string evalDiv(string num1, string num2){
    if(num2 == "0"){
        throw invalid_argument("Math error");
    }
    // Pokud je některý z operandů desetinné číslo, tak se provede operace s double
    if(num1.find('.') != string::npos || num2.find('.') != string::npos){
        double x = stod(num1);
        double y = stod(num2);
        return doubleToString(x/y);
    }
    // Jinak se operandy převedou na long long
    else{
        long long x = stoll(num1);
        long long y = stoll(num2);
        // Pokud by výsledek byl desetinné číslo, tak se provede operace s double
        if(x%y > 0){
            double x = stod(num1);
            double y = stod(num2);
            return doubleToString(x/y);
        }
        return to_string(x/y);
    }
}

string evalNeg(string num1){
    // Pokud je některý z operandů desetinné číslo, tak se provede operace s double
    if(num1.find('.') != string::npos){
        double x = stod(num1);
        return doubleToString(-x);
    
    }
    // Jinak se provede operace s long long
    else{
        long long x = stoll(num1);
        return to_string(-x);
    }
}

string evaluateOperation(char op, vector<string> *stack){
    // Proměnné pro ukládání operandů různých typů
    string xs;
    string ys;
    double xd;
    size_t z;
    int exp;

    // Výpočet operace podle zadaného operátoru
    // Pokud operace vyžaduje 2 operandy, které nejsou na zásobníku, tak se vyhodí výjimka
    // Operandy se odeberou ze zásobníku a výsledek se přidá zpět na zásobník
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
            xs = stack->back();
            stack->pop_back();
            return evalNeg(xs);
        case '^':
            if(stack->size() < 2){
                throw invalid_argument("Syntax error");
            }
            // Kontrola jestli je exponent celé číslo
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
            // Kontrola jestli je exponent celé číslo
            for(char c : stack->back()){
                if(c == '.'){
                    throw invalid_argument("Math error");
                }
            }
            exp = stoi(stack->back());
            stack->pop_back();
            return doubleToString(root(exp,xd));
        case '!':
            // Kontrola jestli se dá vypočítat faktoriál
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
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(csin(xd));
        case 'c':
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(ccos(xd));
        case 't':
            xd = stod(stack->back());
            stack->pop_back();
            return doubleToString(ctan(xd));
        // Pokud by byl načtený neznámý operátor, tak se vyhodí výjimka
        // Nikdy by se nemělo provést, ale bez default se program nepřeloží
        default :
            throw invalid_argument("Syntax error");
    }
}

string evaluate(vector<string> postfixExpression){
    // Cyklus, který vyhodnocuje výraz, dokud není výsledek
    while(postfixExpression.size() > 1){
        vector<string> stack;
        bool flag = false; // true, pokud byla provedena operace
        size_t idx = 0;

        // Cyklus procházející všechny tokeny
        for(string token : postfixExpression){
            // Pokud je token operátor, tak se provede operace
            if(token.length() == 1 && isOperator(token[0]) && flag == false){
                string result = evaluateOperation(token[0], &stack);
                stack.push_back(result);
                flag = true;
            }
            // Pokud je více čísel na zásobníku, ale operátor na zásobníku není
            // tak se vyhodí výjimka
            else if(idx == postfixExpression.size()-1 && flag == false){
                throw invalid_argument("Syntax error");
            }
            // Jinak se token přidá na zásobník
            else{
                stack.push_back(token);
            }
            idx++;
        }
        // Výraz po operaci se uloží zpět na vstup
        postfixExpression = stack;
    }
    return postfixExpression.front();
}

string removeMultSpaces(string expression){
    string result;
    bool prevIsSpace = false;
    for(char c : expression){ // Cyklus procházející všechny znaky ve vstupním řetězci
        if(c == ' '){
            // Pokud je předchozí znak mezera, tak se nevloží další mezera
            if(!prevIsSpace){
                result.push_back(c);
            }
            prevIsSpace = true;
        }else{
            // Pokud znak není mezera, tak se vloží do výsledku
            result.push_back(c);
            prevIsSpace = false;
        }
    }
    return result;
}

string pairParenthesis(string expression){
    int cnt = 0;
    // Počítá kolik závorek je otevřených oproti uzavřeným.
    for(char c : expression){
        if(c == '('){
            cnt++;
        }
        if(c == ')'){
            cnt--;
        }
        // Pokud je více závorek uzavřených než otevřených, tak vyhodí výjimku.
        if(cnt < 0){
            throw invalid_argument("Parenthesis mismatch");
        }
    }
    // Přidává závorky na konec výrazu, dokud není počet otevřených a uzavřených závorek stejný.
    while(cnt > 0){
        expression.append(")");
        cnt--;
    }
    return expression;
}

string formatInput(string expression){
    // Odstranění přebytečných mezer
    expression = removeMultSpaces(expression);
    // Uzavření závorek
    expression = pairParenthesis(expression);
    
    // Zkrácení goniometrických funkcí
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

    // Implicitní odmocnina 2
    idx = 0;
    while(true){ // Cyklus hledající všechny výskyty odmocniny
        idx = expression.find('#',idx);
        // Pokud nenajde další výskyt odmocniny, cyklus se ukončí
        if(idx == string::npos){
            break;
        }
        // Pokud je odmocnina na začátku výrazu, tak se přidá 2
        if(idx == 0){
            expression.insert(0,1,'2');
            idx = idx+2;
            continue;
        }

        size_t idx2 = idx-1; // Index před odmocninou
        char c = expression[idx2];
        // Pokud je před odmocninou mezera na začátku výrazu, tak se nahradí 2
        if(idx2 == 0 &&  c == ' '){
            expression.replace(0,1,"2");
            idx++;
            continue;
        }
        // Pokud je před odmocninou mezera, tak se posune index
        if(c == ' '){
            idx2--;
            c = expression[idx2];
        }
        // Pokud není před odmocninou číslo nebo závorka, tak se přidá 2
        if(isdigit(c) || c == ')'){
            // Pusuneme první index
            idx++;
            continue;
        }
        expression.insert(idx2+1,1,'2');
        // Pusuneme první index
        idx = idx+2;
    }
    
    // Implicitní mocnina 2
    idx = 0;
    while(true){ // Cyklus hledající všechny výskyty mocniny
        idx = expression.find('^',idx);
        // Pokud nenajde další výskyt mocniny, cyklus se ukončí
        if(idx == string::npos){
            break;
        }
        // Pokud je mocnina na konci výrazu, tak se přidá 2
        if(idx == expression.size()-1){
            expression.append("2");
            break;
        }

        size_t idx2 = idx+1; // Index za mocninou
        // Pokud je za mocninou mezera na konci výrazu, tak se nahradí 2
        char c = expression[idx2];
        if(idx2 == expression.size()-1 &&  c == ' '){
            expression.replace(expression.size()-1,1,"2");
            break;
        }
        // Pokud je za mocninou mezera, tak se posune index
        if(c == ' '){
            idx2++;
            c = expression[idx2];
        }
        // Pokud není za mocninou číslo nebo závorka, tak se přidá 2
        if(isdigit(c) || c == '(' || c == '+' || c == '-'){
            // Pusuneme první index
            idx++;
            continue;
        }
        expression.insert(idx2,1,'2');
        // Pusuneme první index
        idx = idx+2;
    }
    return expression;
}

string calculate(string expression){
    // Kontrola, zda je výraz prázdný
    bool noNum = true;
    for(char c : expression){
        if(isdigit(c)){
            noNum = false;
            break;
        }
    }
    // Pokud výraz neobsahuje žádné číslo, tak se vrátí 0
    if(noNum == true){
        return "0";
    }

    // Naformátuje se výraz
    expression = formatInput(expression);
    // Převede se výraz na tokeny
    vector<string> tokens = parse(expression);
    // Převede se výraz na postfixový tvar
    tokens = postfix(tokens);
    // Vyhodnotí se výraz
    return evaluate(tokens);
}

/*** Konec souboru cat_calc_core.cpp ***/