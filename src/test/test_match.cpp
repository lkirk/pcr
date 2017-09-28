#include "gtest/gtest.h"

#define TESTING
extern "C" {
#include "../match.h"
}

class PcrTestSuite : public testing::Test
{
    void SetUp(){}
    void TearDown(){}
};

TEST_F(PcrTestSuite, match_n_chars_found)
{
    char *chars_to_match = "TTGGCTGAAGTAGGTAATATGCCGGCTAG";
    EXPECT_STREQ(match_n_chars("TTGGCT", 6, chars_to_match, 29), chars_to_match);
}

// TEST_F(PcrTestSuite, match_char_ratio_)
// {
//     char *chars_to_match = "TTGGCTGAAGTAGGTAATATGCCGGCTAG";
//     EXPECT_TRUE(match_char_ratio("TTGGCT", chars_to_match, 29, 2));
// }
