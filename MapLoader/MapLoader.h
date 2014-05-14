#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QList>

class QLabel;
class QString;
class QWidget;
class MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    //load ui
    QWidget* loadMap(const QString& strMapPath);

    //load Terrain
    QList<QLabel *> loadMapTerrain(const QWidget* map);

private:

};

#endif // MAPLOADER_H
