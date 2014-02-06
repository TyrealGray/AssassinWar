#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QList>

#include "maploader_global.h"

class QLabel;
class QString;
class QWidget;
class MAPLOADER_EXPORT MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    QWidget* LoadMap(const QString& strMapPath);
    QList<QLabel *> LoadMapTerrain(const QWidget& map);
private:

};

#endif // MAPLOADER_H
