// #include "match.h"
#include "gtest/gtest.h"

#define TESTING

class MyAppTestSuite : public testing::Test
{
  void SetUp(){}
  void TearDown(){}
};

TEST_F(MyAppTestSuite, do_the_thing) {
  EXPECT_EQ(10, 10);
}
