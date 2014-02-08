#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QList>

class QLabel;
class QString;
class QWidget;
class UnderGrid;
class MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    void initMapLoader();

    //读取ui
    QWidget* LoadMap(const QString& strMapPath);

    //读取障碍物场景
    QList<QLabel *> LoadMapTerrain(const QWidget& map);

private:
    UnderGrid* m_pUnderGrid;
};

#endif // MAPLOADER_H
