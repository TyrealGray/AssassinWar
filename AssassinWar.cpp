#include <QPainter>
#include <QTimer>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags)
{
    ui.setupUi(this);

    //MapLoader mapLoader;
    //QWidget* pMapWidget =  mapLoader.LoadMap("./map/map1.ui");
    //mapLoader.LoadMapTerrain(*pMapWidget);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(300);
}

AssassinWar::~AssassinWar()
{

}

void AssassinWar::paintEvent(QPaintEvent *PaintEvent)
{
    static float a = 0.0f;

    if(60 < a)
    {
        a = 0.0f;
    }

    QPainter painter(this);
    painter.drawLine(++a, 0.0, 15.0, 25.0);// drawing code
}