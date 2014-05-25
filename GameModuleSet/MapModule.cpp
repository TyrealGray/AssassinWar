#include "UnderGrid.h"
#include "MapLoader.h"

#include "MapModule.h"
#include "PixelCoordinateTransfer.h"

MapModule::MapModule(void)
    : m_pUnderGrid(NULL),
      m_pMapLoader(NULL)
{
}


MapModule::~MapModule(void)
{
    delete m_pUnderGrid;
    m_pUnderGrid = NULL;

    delete m_pMapLoader;
    m_pMapLoader = NULL;
}

void MapModule::init()
{
    m_pUnderGrid = new UnderGrid();

    m_pMapLoader = new MapLoader();
}

QWidget* MapModule::loadMap(const QString& strMapPath)
{
    m_pMapWidget = m_pMapLoader->loadMap(strMapPath);
    return m_pMapWidget;
}

void MapModule::setGrid(const unsigned int& uiX, const unsigned int& uiY, bool isAble)
{
    m_pUnderGrid->setGrid(uiX, uiY, isAble);
}

bool MapModule::getGrid(const unsigned int& uiX, const unsigned int& uiY)
{
    return ((NULL == m_pUnderGrid->getGrid(uiX, uiY)) ? false : m_pUnderGrid->getGrid(uiX, uiY)->isAble());
}

void MapModule::setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridHeight)
{
    m_uiWidth = uiGridWidth;
    m_uiHeight = uiGridHeight;
    m_pUnderGrid->setSize(uiGridWidth, uiGridHeight);
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

unsigned int MapModule::getWidth()
{
    return m_uiWidth;
}

unsigned int MapModule::getHeight()
{
    return m_uiHeight;
}