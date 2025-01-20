#include "Shape/Rectangle.h"
#include <gtest/gtest.h>

TEST(RectangleTest, CreateRectangle) {
    RectangleC rect(100, 100, 250, 80);
    EXPECT_EQ(rect.GetX(), 100);
    EXPECT_EQ(rect.GetY(), 100);
    EXPECT_EQ(rect.GetWidth(), 250);
    EXPECT_EQ(rect.GetHeight(), 80);
}

TEST(RectangleTest, InvalidDimensions) {
    EXPECT_THROW(RectangleC(100, 100, -250, 80), std::invalid_argument);
    EXPECT_THROW(RectangleC(100, 100, 250, -80), std::invalid_argument);
}

TEST(RectangleTest, NoIntersection) {
    RectangleC rect1(0, 0, 50, 50);
    RectangleC rect2(100, 100, 50, 50);
    
    EXPECT_FALSE(rect1.IntersectsWith(rect2));
}

TEST(RectangleTest, BorderOverlap) {
    RectangleC rect1(0, 0, 10, 10);
    RectangleC rect2(10, 0, 10, 10);
    
    // Border overlap is not intersection
    EXPECT_FALSE(rect1.IntersectsWith(rect2));
}

TEST(RectangleTest, HasIntersection) {
    RectangleC rect1(100, 100, 250, 80);
    RectangleC rect2(140, 160, 250, 100);
    
    EXPECT_TRUE(rect1.IntersectsWith(rect2));
}

TEST(RectangleTest, GetIntersectionRectangle) {
    RectangleC rect1(0, 0, 100, 100);
    RectangleC rect2(50, 50, 100, 100);
    
    EXPECT_TRUE(rect1.IntersectsWith(rect2));

    auto intersection = rect1.GetIntersection(rect2);
    ASSERT_TRUE(intersection.has_value());
    
    auto rect = intersection.value();
    EXPECT_EQ(rect.GetX(), 50);
    EXPECT_EQ(rect.GetY(), 50);
    EXPECT_EQ(rect.GetWidth(), 50);
    EXPECT_EQ(rect.GetHeight(), 50);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}