#pragma once

#include <cstdint>

class RectangleC 
{
public:
    RectangleC(int32_t iX, int32_t iY, int32_t iWidth, int32_t iHeight);
    
    int32_t GetX() const;
    int32_t GetY() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    int32_t mX;
    int32_t mY;
    int32_t mWidth;
    int32_t mHeight;
};
