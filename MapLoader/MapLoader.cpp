#include <QWidget>
#include <QLabel>
#include <QString>
#include <QUiLoader>
#include <QFile>

#include "MapLoader.h"

MapLoader::MapLoader()
{

}

MapLoader::~MapLoader()
{

}

QWidget* MapLoader::LoadMap(const QString& strMapPath)
{
    QUiLoader loader;
    QFile file(strMapPath);
    QWidget *mapWidget = NULL;

    if(file.open(QFile::ReadOnly))
    {
        mapWidget = loader.load(&file);
    }
    else
    {
    }

    file.close();

    return mapWidget;
}

QList<QLabel *> MapLoader::LoadMapTerrain(const QWidget& map)
{
    QList<QLabel *> allTerrains = map.findChildren<QLabel *>();
    return allTerrains;
}