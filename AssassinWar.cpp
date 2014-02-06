#include <QPainter>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags)
{
    ui.setupUi(this);

    //MapLoader mapLoader;
    //QWidget* pMapWidget =  mapLoader.LoadMap("./map/map1.ui");
    //mapLoader.LoadMapTerrain(*pMapWidget);
}

AssassinWar::~AssassinWar()
{

}

void AssassinWar::paintEvent(QPaintEvent *PaintEvent)
{
    QPainter painter(this);
    painter.begin(this);
    painter.drawLine(0.0, 0.0, 15.0, 25.0);// drawing code
    painter.end();
}