#pragma once

class QReadWriteLock;
class Grid
{
public:
    Grid(void);
    Grid(const unsigned int &uiX, const unsigned int &uiY);
    Grid(const Grid& grid);
    ~Grid(void);

    void setAble(const bool &bDisable);

    void setX(const unsigned int &uiX);

    void setY(const unsigned int &uiY);

    bool isAble();

    unsigned int getX();

    unsigned int getY();

private:
    QReadWriteLock* m_pLock;
    bool m_bAble;
    unsigned int m_uiX;
    unsigned int m_uiY;
};

