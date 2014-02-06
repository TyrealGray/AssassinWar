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

    QWidget* LoadMap(const QString& strMapPath);
    QList<QLabel *> LoadMapTerrain(const QWidget& map);
private:

};

#endif // MAPLOADER_H
