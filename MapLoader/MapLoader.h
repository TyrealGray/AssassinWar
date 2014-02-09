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

    void InitMapLoader();

    //load ui
    QWidget* LoadMap(const QString& strMapPath);

    //load Terrain
    QList<QLabel *> LoadMapTerrain(const QWidget& map);

private:

};

#endif // MAPLOADER_H
