#include <QWidget>
#include <QLabel>
#include <QString>
#include <QUiLoader>
#include <QFile>

#include "MapLoader.h"
#include "UnderGrid.h"

MapLoader::MapLoader()
    : m_pUnderGrid(NULL)
{

}

MapLoader::~MapLoader()
{
    if(NULL != m_pUnderGrid)
    {
        delete m_pUnderGrid;
    }
}

QWidget* MapLoader::LoadMap(const QString& strMapPath)
{
    QUiLoader loader;
    QFile file(strMapPath);
    QWidget *pMapWidget = NULL;

    if(file.open(QFile::ReadOnly))
    {
        pMapWidget = loader.load(&file);
    }
    else
    {
        // do nothing
    }

    file.close();

    return pMapWidget;
}

QList<QLabel *> MapLoader::LoadMapTerrain(const QWidget& map)
{
    QList<QLabel *> allTerrains = map.findChildren<QLabel *>();
    return allTerrains;
}

void MapLoader::initMapLoader()
{
    m_pUnderGrid = new UnderGrid();
}