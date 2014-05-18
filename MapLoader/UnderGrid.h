#pragma once
#include <vector>
#include <memory>
#include "Grid.h"

class UnderGrid
{
public:
    UnderGrid(void);
    ~UnderGrid(void);

    //set UnderGrid Size
    //Number of Grid = width*height
    void setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    //get Grid.X=uiX && Grid.Y=uiY
    //return Null if Grid doesn't exist
    std::shared_ptr<Grid> getGrid(const unsigned int &uiX, const  unsigned int &uiY);

    void disableGrids(const unsigned int &uiLeftTopGridX, const unsigned int &uiLeftTopGridY,
                      const unsigned int &uiRightBottomGridX, const unsigned int &uiRightBottomGridY);

private:
    QReadWriteLock* m_pLock;
    bool m_bIsSizeSetted;
    unsigned int m_uiAllGridTotalRow;
    unsigned int m_uiAllGridTotalColumn;
    std::vector<std::shared_ptr<Grid>> m_vecGridGroup;

    std::shared_ptr<Grid> createNewGrid(const unsigned int &uiX, const  unsigned int &uiY);
};

