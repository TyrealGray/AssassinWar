#include <QReadWriteLock>

#include "UnderGrid.h"


UnderGrid::UnderGrid(void)
    : m_pLock(NULL),
      m_bIsSizeSetted(false),
      m_uiAllGridTotalRow(0),
      m_uiAllGridTotalColumn(0)
{
    m_pLock = new QReadWriteLock();
    m_vecGridGroup.reserve(800);
}


UnderGrid::~UnderGrid(void)
{
    delete m_pLock;
    m_pLock = NULL;
}

void UnderGrid::setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight)
{
    if(m_bIsSizeSetted)
    {
        m_vecGridGroup.clear();
        m_vecGridGroup.reserve(800);
    }

    m_uiAllGridTotalColumn = uiGridWidth;
    m_uiAllGridTotalRow = uiGridheight;
    for(unsigned int uiHeightIndex = 0; uiHeightIndex < uiGridheight ; ++uiHeightIndex)
    {
        for(unsigned int uiWidthIndex = 0 ; uiWidthIndex < uiGridWidth; ++uiWidthIndex)
        {
            m_vecGridGroup.push_back(createNewGrid(uiWidthIndex, uiHeightIndex));
        }
    }
    m_bIsSizeSetted = true;
}

std::shared_ptr<Grid> UnderGrid::getGrid(const unsigned int &uiX, const  unsigned int &uiY)
{
    std::shared_ptr<Grid> pGrid = NULL;

    if(m_vecGridGroup.size() > (uiY * m_uiAllGridTotalColumn) + uiX)
    {
        m_pLock->lockForRead();
        pGrid = m_vecGridGroup[(uiY * m_uiAllGridTotalColumn) + uiX ];
        m_pLock->unlock();
    }
    else
    {
        // out of size
    }
    return pGrid;
}

void UnderGrid::disableGrids(const unsigned int &uiLeftTopGridX, const unsigned int &uiLeftTopGridY,
                             const unsigned int &uiRightBottomGridX, const unsigned int &uiRightBottomGridY)
{
    for(unsigned int uiColumnIndex = uiLeftTopGridY; uiColumnIndex <= uiRightBottomGridY; ++uiColumnIndex)
    {
        for(unsigned int uiRowIndex = uiLeftTopGridX; uiRowIndex <= uiRightBottomGridX; ++uiRowIndex)
        {
            m_pLock->lockForRead();
            std::shared_ptr<Grid> pGrid = getGrid(uiRowIndex, uiColumnIndex);
            m_pLock->unlock();

            if(NULL != pGrid)
            {
                m_pLock->lockForWrite();
                pGrid->setAble(false);
                m_pLock->unlock();
            }
        }
    }
}

std::shared_ptr<Grid> UnderGrid::createNewGrid(const unsigned int &uiX, const  unsigned int &uiY)
{
    std::shared_ptr<Grid> pGrid(new Grid(uiX, uiY));
    return pGrid;
}