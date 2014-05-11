#include "UnderGrid.h"
#include "MapLoader.h"

#include "MapModule.h"
#include "MapManager.h"
#include "PixelCoordinateTransfer.h"

MapModule::MapModule(void)
    : m_pUnderGrid(NULL),
      m_pMapLoader(NULL)
{
}


MapModule::~MapModule(void)
{
}

void MapModule::init()
{
    m_pUnderGrid = new UnderGrid();

    m_pMapLoader = new MapLoader();
}

QWidget* MapModule::loadMap(const QString& strMapPath)
{
    m_pMapWidget = m_pMapLoader->loadMap(MapManager::instance().getMapPath(strMapPath));
    return m_pMapWidget;
}

bool MapModule::getGrid(const unsigned int& uiX, const unsigned int& uiY)
{
    std::shared_ptr<Grid> pGrid = m_pUnderGrid->getGrid(uiX, uiY);

    return ((NULL == pGrid) ? false : pGrid->isAble());
}

void MapModule::setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight)
{
    m_pUnderGrid->setSize(uiGridWidth, uiGridheight);
}

void MapModule::loadTerrain()
{
    m_terrainsList = m_pMapLoader->loadMapTerrain(m_pMapWidget);

    for(unsigned int index = 0; index < m_terrainsList.size(); ++index)
    {
        unsigned int iTerrainTopLX = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().left());
        unsigned int iTerrainTopLY = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().top());

        unsigned int iTerrainBottomRX = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().right());
        unsigned int iTerrainBottomRY = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().bottom());

        m_pUnderGrid->disableGrids(
            iTerrainTopLX,
            iTerrainTopLY,
            iTerrainBottomRX,
            iTerrainBottomRY
        );
    }
}