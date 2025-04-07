#include <gtest/gtest.h>

#include "maze.hpp"
#include "path.hpp"
#include "point.hpp"

// Test the Point class
TEST(PointTest, BasicFunctionality)
{
    Point p(1, 2, 1);  // Create a path point at (1,2)

    EXPECT_EQ(p.getRow(), 1);
    EXPECT_EQ(p.getCol(), 2);
    EXPECT_TRUE(p.isPath());
}

// Test Point equality
TEST(PointTest, Equality)
{
    Point p1(1, 2, 1);
    Point p2(1, 2, 1);
    Point p3(2, 3, 1);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Always passing test
TEST(BasicTest, AlwaysPasses) { EXPECT_TRUE(true); }