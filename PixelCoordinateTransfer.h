#pragma once
class PixelCoordinateTransfer
{
public:
    static PixelCoordinateTransfer& Instance();

    int ToGridX(const float& fX);

    int ToGridY(const float& fY);

    float GridXToPixelCoordinateX(const unsigned int& uiX);

    float GridYToPixelCoordinateY(const unsigned int& uiY);
private:
    PixelCoordinateTransfer(void);
    ~PixelCoordinateTransfer(void);
};

