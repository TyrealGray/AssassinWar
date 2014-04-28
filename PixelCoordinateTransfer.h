#pragma once
class PixelCoordinateTransfer
{
public:

    static unsigned int toGrid(const int &iPixelCoordinate);

    static int toPixel(const unsigned int &uiGridCoordinate);

};

