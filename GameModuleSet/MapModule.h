#pragma once
#include <QList>
#include <QLabel>

class UnderGrid;
class MapLoader;
class MapModule
{
public:
    MapModule(void);
    ~MapModule(void);

    void init();

    QWidget* loadMap(const QString& strMapPath);

    void setGrid(const unsigned int& uiX, const unsigned int& uiY, bool isAble);

    bool getGrid(const unsigned int& uiX, const unsigned int& uiY);

    void setSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    void loadTerrain();

private:
    QWidget * m_pMapWidget;
    UnderGrid* m_pUnderGrid;
    MapLoader* m_pMapLoader;
    QList<QLabel *> m_terrainsList;
};

