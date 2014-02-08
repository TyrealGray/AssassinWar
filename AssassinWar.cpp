#include <QPainter>
#include <QTimer>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL),
      m_pMapLoader(NULL)
{

}

AssassinWar::~AssassinWar()
{
    m_pRepaintTimer->stop();
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

bool AssassinWar::initAW()
{
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);

    m_pMapLoader = new MapLoader();
    m_pMapLoader->initMapLoader();
    //QWidget* pMapWidget =  m_pMapLoader->LoadMap("./map/map1.ui");
    //mapLoader->LoadMapTerrain(*pMapWidget);
    return true;
}