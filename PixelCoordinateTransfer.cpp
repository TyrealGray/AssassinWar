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

unsigned int PixelCoordinateTransfer::toGridX(const int& iX)
{
    unsigned int GridX = static_cast<unsigned int>(iX);
    GridX /= 15;
    return GridX + 1;
}

unsigned int PixelCoordinateTransfer::toGridY(const int& iY)
{
    unsigned int GridY = static_cast<unsigned int>(iY);
    GridY /= 15;
    return GridY + 1;
}

int PixelCoordinateTransfer::gridXToPixelCoordinateX(const unsigned int& uiX)
{
    int PixelCoordinateX = static_cast<int>((uiX * 15) + 7);
    return PixelCoordinateX;
}

int PixelCoordinateTransfer::gridYToPixelCoordinateY(const unsigned int& uiY)
{
    int PixelCoordinateY = static_cast<int>((uiY * 15) + 7);
    return PixelCoordinateY;
}