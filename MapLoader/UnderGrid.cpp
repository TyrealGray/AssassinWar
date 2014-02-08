#include "UnderGrid.h"


UnderGrid::UnderGrid(void)
    : m_bIsSizeSetted(false)
{
    m_vecGridGroup.reserve(500);
}


UnderGrid::~UnderGrid(void)
{
}

bool UnderGrid::SetSize(unsigned int &uiGridWidth, unsigned int &uiGridheight)
{
    for(unsigned int uiWidthIndex = 0 ; uiWidthIndex < uiGridWidth; ++uiWidthIndex)
    {
        for(unsigned int uiHeightIndex = 0; uiHeightIndex < uiGridheight ; ++uiHeightIndex)
        {
            m_vecGridGroup.push_back(CreateNewGrid_(uiWidthIndex, uiHeightIndex));
        }
    }
    m_bIsSizeSetted = true;
    return true;
}

std::shared_ptr<Grid> UnderGrid::getGrid(unsigned int &uiX, unsigned int &uiY)
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

std::shared_ptr<Grid> UnderGrid::CreateNewGrid_(unsigned int &uiX, unsigned int &uiY)
{
    std::shared_ptr<Grid> pGrid(new Grid(uiX, uiY));
    return pGrid;
}