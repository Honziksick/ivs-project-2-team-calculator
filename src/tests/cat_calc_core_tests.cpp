#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "cat_calc_core.h"


using namespace ::testing;

TEST(Addition, Integer){
    EXPECT_STREQ("29", calculate("5 + 24"));
    EXPECT_STREQ("29", calculate("5+24"));
    const char* expectedResult = "9209966124358";
    EXPECT_STREQ(expectedResult,
        calculate("8656423001235 + 553543123123"));
    EXPECT_STREQ("0", calculate("0 + 0"));
}

TEST(Addition, Float){
    EXPECT_STREQ("29.0131", calculate("5.004 + 24.0091"));
    EXPECT_STREQ("29.0131", calculate("5.004+24.0091"));
    const char* result = calculate("785463921.0049687712 + 548736291.0091146878");
    EXPECT_STREQ("1334200212.014083459", result);
    EXPECT_STREQ("57.9877", calculate("7.218 + 41.5697 + 2.2 + 7"));
    EXPECT_STREQ("57.9877", calculate("7.218+41.5697+2.2+7"));
}

TEST(Subtraction, Integer){
    EXPECT_STREQ("19", calculate("24 - 5"));
    EXPECT_STREQ("19", calculate("24-5"));
    EXPECT_STREQ("-19", calculate("5 - 24"));
    EXPECT_STREQ("-19", calculate("5-24"));
    const char* expectedResult = "8102879878112";
    EXPECT_STREQ(expectedResult,
        calculate("8656423001235 - 553543123123"));
    EXPECT_STREQ("0", calculate("0 - 0"));
}

TEST(Subtraction, Float){
    EXPECT_STREQ("19.0051", calculate("24.0091 - 5.004"));
    EXPECT_STREQ("19.0051", calculate("24.0091-5.004"));
    EXPECT_STREQ("-19.0051", calculate("5.004 - 24.0091"));
    EXPECT_STREQ("-19.0051", calculate("5.004-24.0091"));
    const char* result = calculate("785463921.0049687712 - 548736291.0091146878");
    EXPECT_STREQ("236727629.9958540834", result);
    EXPECT_STREQ("-43.5517", calculate("7.218 - 41.5697 - 2.2 - 7"));
    EXPECT_STREQ("-43.5517", calculate("7.218-41.5697-2.2-7"));
}



/*** Konec souboru cat_calc_core_tests.cpp ***/
