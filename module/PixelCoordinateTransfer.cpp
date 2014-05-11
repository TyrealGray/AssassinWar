#include "PixelCoordinateTransfer.h"

unsigned int PixelCoordinateTransfer::toGrid(const int &iPixelCoordinate)
{
    unsigned int coordinate = static_cast<unsigned int>(iPixelCoordinate);
    coordinate /= 15;
    return coordinate + 1;
}

int PixelCoordinateTransfer::toPixel(const unsigned int &uiGridCoordinate)
{
    int PixelCoordinate = static_cast<int>((uiGridCoordinate - 1) * 15);
    return PixelCoordinate;
}