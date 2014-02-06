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
    file.open(QFile::ReadOnly);
    QWidget *mapWidget = loader.load(&file);
    file.close();

    return mapWidget;
}

QList<QLabel *> MapLoader::LoadMapTerrain(const QWidget& map)
{
    QList<QLabel *> allTerrains = map.findChildren<QLabel *>();
    return allTerrains;
}