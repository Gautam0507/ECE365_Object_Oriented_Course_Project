#include "../include/point.hpp"  // Adjust path as needed

#include <gtest/gtest.h>

TEST(oint_test, basic_constructor)
{
    Point p;
    EXPECT_EQ(p.getCol(), 0);
    EXPECT_EQ(p.getRow(), 0);
}
