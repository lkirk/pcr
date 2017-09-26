#include "gtest/gtest.h"

#define TESTING
extern "C" {
#include "../match.h"
}

class MyAppTestSuite : public testing::Test
{
    void SetUp(){}
    void TearDown(){}
};

TEST_F(MyAppTestSuite, match_n_chars_found)
{
    char *chars_to_match = "TTGGCTGAAGTAGGTAATATGCCGGCTAG";
    EXPECT_STREQ(match_n_chars("TTGGCT", 6, chars_to_match, 29), chars_to_match);
}
