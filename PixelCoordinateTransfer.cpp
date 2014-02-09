#include "PixelCoordinateTransfer.h"


PixelCoordinateTransfer::PixelCoordinateTransfer(void)
{
}


PixelCoordinateTransfer::~PixelCoordinateTransfer(void)
{
}

PixelCoordinateTransfer& PixelCoordinateTransfer::Instance()
{
    static PixelCoordinateTransfer pixelCoordinateTransfer;
    return pixelCoordinateTransfer;
}

int PixelCoordinateTransfer::ToGridX(const float& fX)
{
    int GridX = static_cast<int>(fX);
    GridX /= 15;
    return GridX - 1;
}

int PixelCoordinateTransfer::ToGridY(const float& fY)
{
    int GridY = static_cast<int>(fY);
    GridY /= 15;
    return GridY - 1;
}

float PixelCoordinateTransfer::GridXToPixelCoordinateX(const unsigned int& uiX)
{
    float PixelCoordinateX = static_cast<float>((uiX + 1) * 15);
    return PixelCoordinateX;
}

float PixelCoordinateTransfer::GridYToPixelCoordinateY(const unsigned int& uiY)
{
    float PixelCoordinateY = static_cast<float>((uiY + 1) * 15);
    return PixelCoordinateY;
}