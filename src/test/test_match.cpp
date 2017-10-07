#include "gtest/gtest.h"

#define TESTING

#include "htslib/faidx.h"
extern "C" {
#include "../match.h"
}

// class FaidxTestFixture: public testing::Test
// {
// protected:
//     faidx_t *fai;
//     void SetUp(){
// 	fai = fai_load("/home/lkirk/references/hg38.fa");
//     }
//     void TearDown(){
// 	fai_destroy(fai);
//     }
// };

TEST(match_n_chars, match)
{
    uint8_t *chars_to_match = (uint8_t*)"TTGGCTGAAGTAGGTAATATGCCGGCTAG";
    EXPECT_EQ(match_n_chars((uint8_t*)"TTGGCT", 6, chars_to_match, 29), chars_to_match);
}

TEST(match_char_ratio, match)
{
    uint8_t *chars_to_match = (uint8_t*)"TTGGCTGAAGTAGGTAATATGCCGGCTAG";
    EXPECT_TRUE(match_char_ratio((uint8_t*)"TTGGCT", chars_to_match, 6, 2));
}

TEST(match_char_ratio, no_match)
{
    uint8_t *chars_to_match = (uint8_t*)"TTGGCTGAAGTAGGTAATATGCCGGCTAG";
    EXPECT_FALSE(match_char_ratio((uint8_t*)"TAGCCG", chars_to_match, 6, 2));
}

// TEST_F(FaidxTestFixture, match_fasta_fetch)
// {
//     int seq_length = 0;
//     char *seq = faidx_fetch_seq(fai, "chr2", 19991, 20040, &seq_length);
//     EXPECT_TRUE(match_char_ratio((char*)"CAGTAACTTGGGGCTCCCAC", seq, 20, 2));
//     free(seq);
// }
