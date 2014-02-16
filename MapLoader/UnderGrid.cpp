#include "UnderGrid.h"


UnderGrid::UnderGrid(void)
    : m_bIsSizeSetted(false),
      m_uiAllGridTotalRow(0),
      m_uiAllGridTotalColumn(0)
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
        m_uiAllGridTotalColumn = uiGridWidth;
        m_uiAllGridTotalRow = uiGridheight;
        for(unsigned int uiHeightIndex = 0; uiHeightIndex < uiGridheight ; ++uiHeightIndex)
        {
            for(unsigned int uiWidthIndex = 0 ; uiWidthIndex < uiGridWidth; ++uiWidthIndex)
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
    std::shared_ptr<Grid> pGrid = NULL;
    if(m_vecGridGroup.size() > (uiY * m_uiAllGridTotalColumn) + uiX)
    {
        pGrid = m_vecGridGroup[(uiY * m_uiAllGridTotalColumn) + uiX ];
    }
    else
    {
        // out of size
    }
    return pGrid;
}

bool UnderGrid::disableGrids(const unsigned int &uiLeftTopGridX, const unsigned int &uiLeftTopGridY,
                             const unsigned int &uiRightBottomGridX, const unsigned int &uiRightBottomGridY)
{
    bool bDisableGridsSuccessed = false;

    for(unsigned int uiColumnIndex = uiLeftTopGridY; uiColumnIndex <= uiRightBottomGridY; ++uiColumnIndex)
    {
        for(unsigned int uiRowIndex = uiLeftTopGridX; uiRowIndex <= uiRightBottomGridX; ++uiRowIndex)
        {
            std::shared_ptr<Grid> pGrid = getGrid(uiRowIndex, uiColumnIndex);
            if(NULL != pGrid)
            {
                pGrid->setDisable(false);
            }
        }
    }

    bDisableGridsSuccessed = true;

    return bDisableGridsSuccessed;
}

std::shared_ptr<Grid> UnderGrid::createNewGrid_(const unsigned int &uiX, const  unsigned int &uiY)
{
    std::shared_ptr<Grid> pGrid(new Grid(uiX, uiY));
    return pGrid;
}