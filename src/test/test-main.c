#include <unity.h>

/* #include <match.h> */

void test_AverageThreeBytes_should_AverageMidRangeValues(void)
{
    TEST_ASSERT_EQUAL_HEX8(40, 40);
    TEST_ASSERT_EQUAL_HEX8(40, 40);
    TEST_ASSERT_EQUAL_HEX8(33, 33);
}

void test_AverageThreeBytes_should_AverageHighValues(void)
{
    TEST_ASSERT_EQUAL_HEX8(80, 80);
    TEST_ASSERT_EQUAL_HEX8(127, 127);
    TEST_ASSERT_EQUAL_HEX8(84, 84);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_AverageThreeBytes_should_AverageMidRangeValues);
    RUN_TEST(test_AverageThreeBytes_should_AverageHighValues);

    return UNITY_END();
}
