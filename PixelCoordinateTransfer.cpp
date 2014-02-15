#include "PixelCoordinateTransfer.h"


PixelCoordinateTransfer::PixelCoordinateTransfer(void)
{
}


PixelCoordinateTransfer::~PixelCoordinateTransfer(void)
{
}

PixelCoordinateTransfer& PixelCoordinateTransfer::instance()
{
    static PixelCoordinateTransfer sPixelCoordinateTransfer;
    return sPixelCoordinateTransfer;
}

unsigned int PixelCoordinateTransfer::toGridX(const float& fX)
{
    unsigned int GridX = static_cast<unsigned int>(fX);
    GridX /= 15;
    return GridX + 1;
}

unsigned int PixelCoordinateTransfer::toGridY(const float& fY)
{
    unsigned int GridY = static_cast<unsigned int>(fY);
    GridY /= 15;
    return GridY + 1;
}

float PixelCoordinateTransfer::gridXToPixelCoordinateX(const unsigned int& uiX)
{
    float PixelCoordinateX = static_cast<float>((uiX * 15) + 7);
    return PixelCoordinateX;
}

float PixelCoordinateTransfer::gridYToPixelCoordinateY(const unsigned int& uiY)
{
    float PixelCoordinateY = static_cast<float>((uiY * 15) + 7);
    return PixelCoordinateY;
}