#pragma once
class PixelCoordinateTransfer
{
public:
    static PixelCoordinateTransfer& instance();

    unsigned int toGridX(const int& iX);

    unsigned int toGridY(const int& iY);

    int gridXToPixelCoordinateX(const unsigned int& uiX);

    int gridYToPixelCoordinateY(const unsigned int& uiY);
private:
    PixelCoordinateTransfer(void);
    ~PixelCoordinateTransfer(void);
};

