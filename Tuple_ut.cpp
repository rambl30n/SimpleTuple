#include <gtest/gtest.h>
#include "Tuple.h"

TEST(tuple, initialize)
{
    Tuple t(1, 'a', 1.2);
    ASSERT_EQ(1, t.get<0>());

    t.get<0>() = 2;
    ASSERT_EQ(2, t.get<0>());

    t.get<1>() = 'c';
    ASSERT_EQ('c', t.get<1>());

    t.get<2>() = 123.45;
    ASSERT_DOUBLE_EQ(123.45, t.get<2>());
}
