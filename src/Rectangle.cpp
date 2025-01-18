#include "Rectangle/Rectangle.h"
#include <stdexcept>

RectangleC::RectangleC(int32_t iX, int32_t iY, int32_t iWidth, int32_t iHeight)
    : mX(iX)
    , mY(iY)
    , mWidth(iWidth)
    , mHeight(iHeight) {
    if (iWidth < 0 || iHeight < 0) {
        throw std::invalid_argument("Width and height must be non-negative");
    }
}

int32_t RectangleC::GetX() const { return mX; }
int32_t RectangleC::GetY() const { return mY; }
int32_t RectangleC::GetWidth() const { return mWidth; }
int32_t RectangleC::GetHeight() const { return mHeight; }