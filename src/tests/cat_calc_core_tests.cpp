#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "cat_calc_core.h"

/** Testovaná přesnost kalkulačky na 14 desetinných míst */
#define TESTED_PRECISION 0.00000000000001

using namespace ::testing;
using namespace std;

/**
 * @brief Porovnává 2 vektory řetězců
 * 
 * @return True, pokud mají vektory stejný obsah, jinak false
*/
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


TEST(Calculate, BasicExpressions){
    string expression = "4";
    string expectedResult= "4";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "9/3";
    expectedResult= "3";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "-5.5/-5.5*-1-1.5";
    expectedResult= "-2.5";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());


    expression = "2!!";
    expectedResult= "2";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "3!!";
    expectedResult= "720";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "#4";
    expectedResult= "2";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "(#4";
    expectedResult= "2";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "  #4";
    expectedResult= "2";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "(1+4)* #16";
    expectedResult= "20";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "5+#81/2";
    expectedResult= "9.5";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "5^";
    expectedResult= "25";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "5^  ";
    expectedResult= "25";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "(2*3^) +1";
    expectedResult= "19";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "2*1+3^(2+1)+2";
    expectedResult= "31";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "4 - (-8)";
    expectedResult= "12";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "3.1+ 8.2";
    expectedResult= "11.3";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "45/4.5";
    expectedResult= "10";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

}

TEST(Calculate, ComplexExpressions){
    degRad = false;
    string expression = "(3.1+ 8.2) * 3 #cos(48)^2";
    string expectedResult= "8.644748712019318";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "sin(4!) *10";
    expectedResult= "4.0673664307580024";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "((sin(4!)+1) *10)+2";
    expectedResult= "16.067366430758";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());
}

TEST(Calculate, Errors){
    string expression = "3*8/(2-2)";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "tan(40)!";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "(-4)!";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "3*5)+4";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "2#-4";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "2.5#3";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "-3#0";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "3^2.5";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "0^(-3)";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "3*/4";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "*89+9";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "89+9*";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "89+9-";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "1 2";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "3/";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "^2";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "2#";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "!*5";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "5*s";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "5*c";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "5*t";
    EXPECT_ANY_THROW(calculate(expression));

    expression = "5*?";
    EXPECT_ANY_THROW(calculate(expression));
}

TEST(Calculate, NoErrors){
    string expression = "3 + (-8)";
    EXPECT_NO_THROW(calculate(expression));
    expression = "3 - (-8)";
    EXPECT_NO_THROW(calculate(expression));
    expression = "3#-8";
    EXPECT_NO_THROW(calculate(expression));
    expression = "89++9";
    EXPECT_NO_THROW(calculate(expression));
    expression = "3";
    EXPECT_NO_THROW(calculate(expression));
    expression = "-3";
    EXPECT_NO_THROW(calculate(expression));
    expression = "3!!";
    EXPECT_NO_THROW(calculate(expression));

    expression = "";
    string expectedResult= "0";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());
    
    expression = "     ";
    expectedResult= "0";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "()((";
    expectedResult= "0";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = ")";
    expectedResult= "0";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

}

TEST(Parse, BasicExpressions){
    vector<string> expected = {"5"};
    vector<string> result = parse("5");
    EXPECT_PRED2(compareVectors, expected, result);

    expected = {"5.4", "+", "4", "!"};
    result = parse("5.4    +4 ! ");
    EXPECT_PRED2(compareVectors, expected, result);
}

TEST(Parse, ComplexExpressions){
    vector<string> expected = {"558", "*", "0.5", "-", "(", "~", "2", ")",
                                "+", "2", "#", "3", "^", "4"};
    vector<string> result = parse(" 558*0.5 - (-2) + 2#3^4 ");
    EXPECT_PRED2(compareVectors, expected, result);
}

TEST(Postfix, BasicExpressions){
    vector<string> expected = {"5"};
    vector<string> result = postfix({"5"});
    EXPECT_PRED2(compareVectors, expected, result);

    expected = {"5.4", "4", "!", "+"};
    result = postfix({"5.4", "+", "4", "!"});
    EXPECT_PRED2(compareVectors, expected, result);
}

TEST(Postfix, ComplexExpressions){
    vector<string> expected = {"558", "0.5", "*", "2", "~", "-",
                                 "2", "3", "4", "^", "#", "+"};
    vector<string> result = postfix({"558", "*", "0.5", "-", "(", "~",
                                    "2", ")", "+", "2", "#", "3", "^", "4"});
    EXPECT_PRED2(compareVectors, expected, result);
}


TEST(Evaluate, BasicExpressions){
    string expected = "5";
    string result = evaluate({"5"});
    EXPECT_STREQ(expected.c_str(), result.c_str());

    expected = "29.4";
    result = evaluate({"5.4", "4", "!", "+"});
    EXPECT_STREQ(expected.c_str(), result.c_str());
}

TEST(Evaluate, ComplexExpressions){
    string expected = "290";
    string result = evaluate({"558", "0.5", "*", "2", "~", "-",
                                 "2", "3", "4", "^", "#", "+"});
    EXPECT_STREQ(expected.c_str(), result.c_str());
}

TEST(Operations, AbsoluteValue){
    EXPECT_EQ(15, absVal(15));
    EXPECT_EQ(15, absVal(-15));
}

TEST(Operations, Root){
    EXPECT_EQ(5, root(2,25));
    EXPECT_EQ(2, root(12,4096));
    EXPECT_EQ(0.5, root(-3,8));
    EXPECT_EQ(-3, root(3,-27));
    EXPECT_EQ(-1, root(3,-1));
    EXPECT_NEAR(1.286648351223739, root(3, 2.13), TESTED_PRECISION);
    EXPECT_NEAR(1.732050807568877, root(2,3), TESTED_PRECISION);
    EXPECT_NEAR(0.3894322904960899, root(4,0.023), TESTED_PRECISION);
    EXPECT_NEAR(-0.284386697985156, root(3,-0.023), TESTED_PRECISION);
    double expectedResult = 11111.111060555555441;
    EXPECT_NEAR(expectedResult, root(2,123456789), expectedResult*TESTED_PRECISION);
    EXPECT_ANY_THROW(root(2,-16));
}

TEST(Operations, Power){
    EXPECT_EQ(64, power(2,8));
    EXPECT_EQ(81, power(4,3));
    EXPECT_EQ(0.25, power(-2,2));
    EXPECT_EQ(16, power(2,-4));
    EXPECT_EQ(-64, power(3,-4));

}

TEST(Operations, Sine){
    degRad = true;
    EXPECT_NEAR(0.5, csin(PI/6), TESTED_PRECISION);
    degRad = false;
    EXPECT_NEAR(0.5, csin(30), TESTED_PRECISION);
    EXPECT_NEAR(-0.5, csin(-30), TESTED_PRECISION);
    EXPECT_NEAR(csin(5),csin(365), TESTED_PRECISION);
    EXPECT_NEAR(0.939692620785908, csin(70), TESTED_PRECISION);
}

TEST(Operations, Cosine){
    degRad = true;
    EXPECT_NEAR(0.5, ccos(PI/3), TESTED_PRECISION);
    degRad = false;
    EXPECT_NEAR(0.5,ccos(60), TESTED_PRECISION);
    EXPECT_NEAR(0.5,ccos(-60), TESTED_PRECISION);
    EXPECT_NEAR(ccos(6),ccos(366), TESTED_PRECISION);
    EXPECT_NEAR(0.342020143325668, ccos(70), TESTED_PRECISION);
}

TEST(Operations, Tan){
    degRad = true;
    EXPECT_NEAR(1,ctan(PI/4), TESTED_PRECISION);
    degRad = false;
    EXPECT_NEAR(1,ctan(45), TESTED_PRECISION);
    EXPECT_NEAR(ctan(24),ctan(204), TESTED_PRECISION);
    EXPECT_NEAR(2.747477419454622, ctan(70), TESTED_PRECISION);
    EXPECT_ANY_THROW(ctan(270));
}

TEST(Operations, Factorial){
    size_t expectedResult = 24;
    EXPECT_EQ(expectedResult,factorial(4));
    expectedResult = 2432902008176640000;
    EXPECT_EQ(expectedResult,factorial(20));
    EXPECT_ANY_THROW(factorial(-5));
}

TEST(Other, IsOperator){
    string testExpression = "4 /(7+1.2)";
    bool expectedResult[] = {false,false,true,false,false,true,false,false,false,false};
    for(int i = 0; i < 10; i++){
        EXPECT_EQ(expectedResult[i], isOperator(testExpression[i]));
    }
}

/*** Konec souboru cat_calc_core_tests.cpp ***/