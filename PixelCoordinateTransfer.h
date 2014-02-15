#pragma once
class PixelCoordinateTransfer
{
public:
    static PixelCoordinateTransfer& instance();

    unsigned int toGridX(const float& fX);

    unsigned int toGridY(const float& fY);

    float gridXToPixelCoordinateX(const unsigned int& uiX);

    float gridYToPixelCoordinateY(const unsigned int& uiY);
private:
    PixelCoordinateTransfer(void);
    ~PixelCoordinateTransfer(void);
};

