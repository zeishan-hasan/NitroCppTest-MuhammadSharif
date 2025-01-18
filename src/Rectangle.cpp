#include "Rectangle/Rectangle.h"
#include <stdexcept>
#include <algorithm>

RectangleC::RectangleC(int32_t iX, int32_t iY, int32_t iWidth, int32_t iHeight)
    : mX(iX)
    , mY(iY)
    , mWidth(iWidth)
    , mHeight(iHeight) 
{
    if (iWidth < 0 || iHeight < 0) {
        throw std::invalid_argument("Width and height must be non-negative");
    }
}

int32_t RectangleC::GetX() const { return mX; }
int32_t RectangleC::GetY() const { return mY; }
int32_t RectangleC::GetWidth() const { return mWidth; }
int32_t RectangleC::GetHeight() const { return mHeight; }

bool RectangleC::IntersectsWith(const RectangleC& iOther) const 
{
    // Even border overlap is not intersection
    if ((mX + mWidth <= iOther.mX) || 
        (iOther.mX + iOther.mWidth <= mX) ||
        (mY + mHeight <= iOther.mY) ||
        (iOther.mY + iOther.mHeight <= mY))
    {
        return false;
    }

    return true;
}

std::optional<RectangleC> RectangleC::GetIntersection(const RectangleC& iOther) const 
{
    if (!IntersectsWith(iOther)) {
        return std::nullopt;
    }

    // Get intersection rectangle coordinates
    int32_t intersectX = std::max(mX, iOther.mX);
    int32_t intersectY = std::max(mY, iOther.mY);
    
    // Calculate intersection rectangle dimensions
    int32_t intersectWidth = std::min(mX + mWidth, iOther.mX + iOther.mWidth) - intersectX;
    int32_t intersectHeight = std::min(mY + mHeight, iOther.mY + iOther.mHeight) - intersectY;

    return RectangleC(intersectX, intersectY, intersectWidth, intersectHeight);
}