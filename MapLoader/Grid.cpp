#include <QReadWriteLock>

#include "Grid.h"


Grid::Grid(void)
{
}

Grid::Grid(const unsigned int &uiX, const unsigned int &uiY)
    : m_bAble(true),
      m_uiX(uiX),
      m_uiY(uiY)
{
    m_pLock = new QReadWriteLock();
}

Grid::Grid(const Grid& grid)
{
    m_bAble = grid.m_bAble;
    m_uiX = grid.m_uiX;
    m_uiY = grid.m_uiY;
}

Grid::~Grid(void)
{
    delete m_pLock;
    m_pLock = NULL;
}

void Grid::setAble(const bool &bDisable)
{
    m_pLock->lockForWrite();
    m_bAble = bDisable;
    m_pLock->unlock();
}

void Grid::setX(const unsigned int &uiX)
{
    m_pLock->lockForWrite();
    m_uiX = uiX;
    m_pLock->unlock();
}

void Grid::setY(const unsigned int &uiY)
{
    m_pLock->lockForWrite();
    m_uiY = uiY;
    m_pLock->unlock();
}

bool Grid::isAble()
{
    return m_bAble;
}

unsigned int Grid::getX()
{
    return m_uiX;
}

unsigned int Grid::getY()
{
    return m_uiY;
}