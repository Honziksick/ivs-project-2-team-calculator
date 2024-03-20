#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "cat_calc_core.h"

/** Testovaná přesnost kalkulačky */
#define PRECISION 0.00000000000001

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

    expression = "";
    expectedResult= "";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());
    
    expression = "     ";
    expectedResult= "";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "2!!";
    expectedResult= "24";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "4 - (-8)";
    expectedResult= "12";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "3.1+ 8.2";
    expectedResult= "11.3";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());
}

TEST(Calculate, ComplexExpressions){
    string expression = "(3.1+ 8.2) * 3 #cos(48)^2";
    string expectedResult= "8.644748712019314";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "sin(4!) *10";
    expectedResult= "4.067366430758002";
    EXPECT_STREQ(expectedResult.c_str(), calculate(expression).c_str());

    expression = "((sin(4!)+1) *10)+2";
    expectedResult= "16.067366430758002";
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

    expression = "3#-8";
    EXPECT_NO_THROW(calculate(expression));
}

TEST(FormatCheck, Correct){
    string expression = "3 + (-8)";
    EXPECT_NO_THROW(formatCheck(expression));
    expression = "3 - (-8)";
    EXPECT_NO_THROW(formatCheck(expression));
    expression = "89++9";
    EXPECT_NO_THROW(formatCheck(expression));
    expression = "3";
    EXPECT_NO_THROW(formatCheck(expression));
    expression = "-3";
    EXPECT_NO_THROW(formatCheck(expression));
    expression = "3!!";
    EXPECT_NO_THROW(formatCheck(expression));

}

TEST(FormatCheck, Incorrect){
    string expression = "3*/4";
    EXPECT_ANY_THROW(formatCheck(expression));
    expression = "*89+9";
    EXPECT_ANY_THROW(formatCheck(expression));
    expression = "89+9*";
    EXPECT_ANY_THROW(formatCheck(expression));
    expression = "89+9-";
    EXPECT_ANY_THROW(formatCheck(expression));
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
    vector<string> expected = {"558", "*", "0.5", "-", "(", "-", "2", ")",
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
    EXPECT_PRED2(compareVectors, expected, result); //This is the line that doesn't work
}

TEST(Postfix, ComplexExpressions){
    vector<string> expected = {"558", "0.5", "*", "-2", "-",
                                "2", "+", "3", "4", "^", "#"};
    vector<string> result = postfix({"558", "*", "0.5", "-", "(", "-",
                                    "2", ")", "+", "2", "#", "3", "^", "4"});
    EXPECT_PRED2(compareVectors, expected, result);
}


TEST(Evaluate, BasicExpressions){
    string expected = "5";
    string result = evaluate({"5"});
    EXPECT_STREQ(expected.c_str(), result.c_str());

    expected = "29.4";
    result = evaluate({"5.4" "4" "!" "+"});
    EXPECT_STREQ(expected.c_str(), result.c_str());
}

TEST(Evaluate, ComplexExpressions){
    string expected = "290";
    string result = evaluate({"558", "0.5", "*", "-2", "-",
                                "2", "+", "3", "4", "^", "#"});
    EXPECT_STREQ(expected.c_str(), result.c_str());
}

TEST(Operations, AbsoluteValue){
    EXPECT_EQ(15, absVal(15));
    EXPECT_EQ(15, absVal(-15));
}

TEST(Operations, Root){
    EXPECT_EQ(5, root(2,25));
    EXPECT_EQ(2, root(12,4096));
    EXPECT_EQ(-3, root(3,-27));
    EXPECT_NEAR(1.286648351223739, root(3, 2.13), PRECISION);
    EXPECT_NEAR(1.732050807568877, root(2,3), PRECISION);
    EXPECT_NEAR(0.3894322904960899, root(4,0.023), PRECISION);
    EXPECT_NEAR(-0.284386697985156, root(3,-0.023), PRECISION);
    EXPECT_ANY_THROW(root(2,-16));
}

TEST(Operations, Power){
    EXPECT_EQ(64, power(2,8));
    EXPECT_EQ(81, power(4,3));
    EXPECT_EQ(16, power(2,-4));
    EXPECT_EQ(-64, power(3,-4));

}

TEST(Operations, Sine){
    EXPECT_EQ(0.5, csin(30));
    EXPECT_EQ(-0.5, csin(-30));
    EXPECT_EQ(csin(5),csin(365));
    EXPECT_NEAR(0.939692620785908, csin(70), PRECISION);
}

TEST(Operations, Cosine){
    EXPECT_EQ(0.5,ccos(60));
    EXPECT_EQ(0.5,ccos(-60));
    EXPECT_EQ(ccos(6),ccos(366));
    EXPECT_NEAR(0.342020143325668, ccos(70), PRECISION);
}

TEST(Operations, Tan){
    EXPECT_EQ(1,ctan(45));
    EXPECT_EQ(ctan(24),ctan(204));
    EXPECT_NEAR(2.747477419454622, ctan(70), PRECISION);
    EXPECT_ANY_THROW(ctan(270));
}


/*** Konec souboru cat_calc_core_tests.cpp ***/
