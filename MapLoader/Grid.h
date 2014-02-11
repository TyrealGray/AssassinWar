#pragma once
class Grid
{
public:
    Grid(void);
    Grid(const unsigned int &uiX, const unsigned int &uiY);
    Grid(const Grid& grid);
    ~Grid(void);

    void setDisable(const bool &bDisable);

    void setX(const unsigned int &uiX);

    void setY(const unsigned int &uiY);

    bool isDisable();

    unsigned int getX();

    unsigned int getY();

private:
    bool m_bDisable;
    unsigned int m_uiX;
    unsigned int m_uiY;
};

