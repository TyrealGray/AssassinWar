#pragma once
class Grid
{
public:
    Grid(void);
    Grid(unsigned int &uiX, unsigned int &uiY);
    Grid(const Grid& grid);
    ~Grid(void);

    //设置是否可以使用该网格
    void SetDisable(bool &bDisable);

    void SetX(unsigned int &uiX);

    void SetY(unsigned int &uiY);

    bool IsDisable();

    unsigned int GetX();

    unsigned int GetY();

private:
    bool m_bDisable;
    unsigned int m_uiX;
    unsigned int m_uiY;
};

