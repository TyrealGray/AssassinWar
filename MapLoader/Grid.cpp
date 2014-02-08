#include "Grid.h"


Grid::Grid(void)
{
}

Grid::Grid(unsigned int &uiX, unsigned int &uiY)
    : m_bDisable(true),
      m_uiX(uiX),
      m_uiY(uiY)
{

}

Grid::Grid(const Grid& grid)
{
    m_bDisable = grid.m_bDisable;
    m_uiX = grid.m_uiX;
    m_uiY = grid.m_uiY;
}

Grid::~Grid(void)
{
}

void Grid::SetDisable(bool &bDisable)
{
    m_bDisable = bDisable;
}

void Grid::SetX(unsigned int &uiX)
{
    m_uiX = uiX;
}

void Grid::SetY(unsigned int &uiY)
{
    m_uiY = uiY;
}

bool Grid::IsDisable()
{
    return m_bDisable;
}

unsigned int Grid::GetX()
{
    return m_uiX;
}

unsigned int Grid::GetY()
{
    return m_uiY;
}