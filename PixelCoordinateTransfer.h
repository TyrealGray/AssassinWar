#pragma once
class PixelCoordinateTransfer
{
public:
    PixelCoordinateTransfer(void);
    ~PixelCoordinateTransfer(void);

    unsigned int ToGridX(unsigned int uiX);

    unsigned int ToGridY(unsigned int uiY);

    unsigned int GridXToPixelCoordinateX(unsigned int uiX);

    unsigned int GridYToPixelCoordinateY(unsigned int uiY);
};

