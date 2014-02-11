#include "UnderGrid.h"


UnderGrid::UnderGrid(void)
    : m_bIsSizeSetted(false)
{
    m_vecGridGroup.reserve(500);
}


UnderGrid::~UnderGrid(void)
{
}

bool UnderGrid::setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight)
{
    bool bSetSizeSuccessed = false;

    if(!m_bIsSizeSetted)
    {
        for(unsigned int uiWidthIndex = 0 ; uiWidthIndex < uiGridWidth; ++uiWidthIndex)
        {
            for(unsigned int uiHeightIndex = 0; uiHeightIndex < uiGridheight ; ++uiHeightIndex)
            {
                m_vecGridGroup.push_back(createNewGrid_(uiWidthIndex, uiHeightIndex));
            }
        }
        m_bIsSizeSetted = true;
        bSetSizeSuccessed = true;
    }
    else
    {
        //do nothing
    }

    return bSetSizeSuccessed;
}

std::shared_ptr<Grid> UnderGrid::getGrid(const unsigned int &uiX, const  unsigned int &uiY)
{
    std::vector<std::shared_ptr<Grid>>::const_iterator vecGridIterator = m_vecGridGroup.begin();
    vecGridIterator += ((uiX + 1)  * (uiY + 1));
    if(m_vecGridGroup.end() == vecGridIterator)
    {
        return NULL;
    }
    else
    {
        return (*vecGridIterator);
    }
}

bool UnderGrid::disableGrids(const unsigned int &uiLeftTopGridX, const unsigned int &uiLeftTopGridY,
                             const unsigned int &uiRightBottomGridX, const unsigned int &uiRightBottomGridY)
{
    return false;
}

std::shared_ptr<Grid> UnderGrid::createNewGrid_(const unsigned int &uiX, const  unsigned int &uiY)
{
    std::shared_ptr<Grid> pGrid(new Grid(uiX, uiY));
    return pGrid;
}