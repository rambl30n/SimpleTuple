#include <gtest/gtest.h>
#include "Tuple.h"
#include <tuple>

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
TEST(tuple, alignment)
{
    struct A { char a_; int b_; char c_; };
    struct C{};
    struct D{char x; double y;};
    struct E{char a; char b; int c;};
    struct F{char a; char b; char c; int d; };
    struct G{char a; char b; char c; char d; int e;};

    Tuple a('a', 123, 'b');
    ASSERT_EQ(sizeof(A), sizeof(a));

    struct alignas(64) X { int x; };

    using tuple_b = std::tuple<char, X, char>;
    Tuple b('a', X{123}, 'b');
    ASSERT_EQ(sizeof(tuple_b), sizeof(b));
}
