#pragma once
class PixelCoordinateTransfer
{
public:
    static PixelCoordinateTransfer& instance();

    int toGridX(const float& fX);

    int toGridY(const float& fY);

    float gridXToPixelCoordinateX(const unsigned int& uiX);

    float gridYToPixelCoordinateY(const unsigned int& uiY);
private:
    PixelCoordinateTransfer(void);
    ~PixelCoordinateTransfer(void);
};

