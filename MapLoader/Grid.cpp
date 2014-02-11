#include "Grid.h"


Grid::Grid(void)
{
}

Grid::Grid(const unsigned int &uiX, const unsigned int &uiY)
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

void Grid::setDisable(const bool &bDisable)
{
    m_bDisable = bDisable;
}

void Grid::setX(const unsigned int &uiX)
{
    m_uiX = uiX;
}

void Grid::setY(const unsigned int &uiY)
{
    m_uiY = uiY;
}

bool Grid::isDisable()
{
    return m_bDisable;
}

unsigned int Grid::getX()
{
    return m_uiX;
}

unsigned int Grid::getY()
{
    return m_uiY;
}