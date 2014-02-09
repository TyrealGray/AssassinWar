#pragma once
class Grid
{
public:
    Grid(void);
    Grid(const unsigned int &uiX, const unsigned int &uiY);
    Grid(const Grid& grid);
    ~Grid(void);

    void SetDisable(const bool &bDisable);

    void SetX(const unsigned int &uiX);

    void SetY(const unsigned int &uiY);

    bool IsDisable();

    unsigned int GetX();

    unsigned int GetY();

private:
    bool m_bDisable;
    unsigned int m_uiX;
    unsigned int m_uiY;
};

