#include "cat_calc_core.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace catMath;

/** Testovaná přesnost kalkulačky na 14 desetinných míst */
#define TESTED_PRECISION 0.00000000000001

bool compareVectors(vector<string> vec1, vector<string> vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }
    
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // BasicExpressions
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

    // ComplexExpressions
    {
        string expression = "(3.1+ 8.2) * 3 #cos(48)^2";
        cout << calculate(expression) << endl;

        expression = "sin(4!) *10";
        cout << calculate(expression) << endl;

        expression = "((sin(4!)+1) *10)+2";
        cout << calculate(expression) << endl;
    }

    // Errors
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

    // NoErrors
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

    // Parse
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

    // Parse_ComplexExpressions
    {
        vector<string> expected = {"558", "*", "0.5", "-", "(", "~", "2", ")",
                                    "+", "2", "#", "3", "^", "4"};
        vector<string> result = parse(" 558*0.5 - (-2) + 2#3^4 ");
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    // Postfix_BasicExpressions
    {
        vector<string> expected = {"5"};
        vector<string> result = postfix({"5"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;

        expected = {"5.4", "4", "!", "+"};
        result = postfix({"5.4", "+", "4", "!"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    // Postfix_ComplexExpressions
    {
        vector<string> expected = {"558", "0.5", "*", "2", "~", "-",
                                     "2", "3", "4", "^", "#", "+"};
        vector<string> result = postfix({"558", "*", "0.5", "-", "(", "~",
                                        "2", ")", "+", "2", "#", "3", "^", "4"});
        cout << (compareVectors(expected, result) ? "PASS" : "FAIL") << endl;
    }

    // Evaluate_BasicExpressions
    {
        string expected = "5";
        string result = evaluate({"5"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;

        expected = "29.4";
        result = evaluate({"5.4", "4", "!", "+"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;
    }

    // Evaluate_ComplexExpressions
    {
        string expected = "290";
        string result = evaluate({"558", "0.5", "*", "2", "~", "-",
                                     "2", "3", "4", "^", "#", "+"});
        cout << (expected == result ? "PASS" : "FAIL") << endl;
    }

    // Operations_AbsoluteValue
    {
        cout << (absVal(15) == 15 ? "PASS" : "FAIL") << endl;
        cout << (absVal(-15) == 15 ? "PASS" : "FAIL") << endl;
    }

    // Operations_Root
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

    // Operations_Power
    {
        cout << (power(2,8) == 64 ? "PASS" : "FAIL") << endl;
        cout << (power(4,3) == 81 ? "PASS" : "FAIL") << endl;
        cout << (power(2,-4) == 16 ? "PASS" : "FAIL") << endl;
        cout << (power(3,-4) == -64 ? "PASS" : "FAIL") << endl;
    }

    // Operations_Sine
    {
        cout << (abs(csin(30) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(-30) + 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(5) - csin(365)) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(csin(70) - 0.939692620785908) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
    }

    // Operations_Cosine
    {
        cout << (abs(ccos(60) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(-60) - 0.5) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(6) - ccos(366)) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
        cout << (abs(ccos(70) - 0.342020143325668) < TESTED_PRECISION ? "PASS" : "FAIL") << endl;
    }

    // Operations_Tan
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

    // Operations_Factorial
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

    // Other_IsOperator
    {
        string testExpression = "4 /(7+1.2)";
        bool expectedResult[] = {false,false,true,false,false,true,false,false,false,false};
        for(int i = 0; i < 10; i++){
            cout << (isOperator(testExpression[i]) == expectedResult[i] ? "PASS" : "FAIL") << endl;
        }
    }

    return 0;
}