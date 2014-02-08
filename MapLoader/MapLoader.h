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

    //��ȡui
    QWidget* LoadMap(const QString& strMapPath);

    //��ȡ�ϰ��ﳡ��
    QList<QLabel *> LoadMapTerrain(const QWidget& map);

private:
    UnderGrid* m_pUnderGrid;
};

#endif // MAPLOADER_H
