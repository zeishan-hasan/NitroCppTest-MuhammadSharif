#include "Rectangle/Rectangle.h"
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

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}