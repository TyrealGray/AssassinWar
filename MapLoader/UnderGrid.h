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
    bool SetSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    //get Grid.X=uiX && Grid.Y=uiY
    //return Null if Grid doesn't exist
    std::shared_ptr<Grid> getGrid(const unsigned int &uiX, const  unsigned int &uiY);

private:
    bool m_bIsSizeSetted;
    std::vector<std::shared_ptr<Grid>> m_vecGridGroup;

    std::shared_ptr<Grid> CreateNewGrid_(const unsigned int &uiX, const  unsigned int &uiY);
};

