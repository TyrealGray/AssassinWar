#pragma once
#include <vector>
#include <memory>
#include "Grid.h"

class UnderGrid
{
public:
    UnderGrid(void);
    ~UnderGrid(void);

    //设置地面网格大小
    //网格数量(Number of Grid) = width*height
    bool SetSize(unsigned int &uiGridWidth, unsigned int &uiGridheight);

    //获取X,Y处的网格get Grid.X=uiX && Grid.Y=uiY
    //如果没有返回Null if Grid doesn't exist
    std::shared_ptr<Grid> getGrid(unsigned int &uiX, unsigned int &uiY);

private:
    bool m_bIsSizeSetted;
    std::vector<std::shared_ptr<Grid>> m_vecGridGroup;

    std::shared_ptr<Grid> CreateNewGrid_(unsigned int &uiX, unsigned int &uiY);
};

