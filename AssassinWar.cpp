#include <QTimer>
#include <QLabel>
#include <QPainter>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"
#include "UnderGrid.h"
#include "PixelCoordinateTransfer.h"

const int GRID_NUMBER_IS_ZERO = -1;

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL),
      m_pMapLoader(NULL),
      m_pUnderGrid(NULL)
{

}

AssassinWar::~AssassinWar()
{
    m_pRepaintTimer->stop();

    if(NULL != m_pMapLoader)
    {
        delete m_pMapLoader;
        m_pMapLoader = NULL;
    }

    if(NULL != m_pUnderGrid)
    {
        delete m_pUnderGrid;
        m_pUnderGrid = NULL;
    }
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
    bool bInitSuccessed = true;
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);

    m_pMapLoader = new MapLoader();
    m_pMapLoader->InitMapLoader();

    m_pUnderGrid = new UnderGrid();

    QString strMapPath = "./map/map1.ui";
    bInitSuccessed = LoadGameMap_(strMapPath);

    setWindowState(Qt::WindowFullScreen);

    return bInitSuccessed;
}

bool AssassinWar::LoadGameMap_(const QString& strMapPath)
{
    bool bLoadGameMapSuccessed = true;

    QWidget* pMapWidget =  m_pMapLoader->LoadMap(strMapPath);
    if(NULL == pMapWidget)
    {
        bLoadGameMapSuccessed = false;
    }
    else
    {
        setCentralWidget(pMapWidget);
        QSize mapSize = pMapWidget->size();

        float fMapWidth = static_cast<float>(mapSize.width());
        float fMapHeight = static_cast<float>(mapSize.height());

        int iAllGridTotalRow = PixelCoordinateTransfer::Instance().ToGridX(fMapWidth);
        int iAllGridTotalColumn = PixelCoordinateTransfer::Instance().ToGridY(fMapHeight);

        if(GRID_NUMBER_IS_ZERO != iAllGridTotalRow && GRID_NUMBER_IS_ZERO != iAllGridTotalColumn)
        {
            unsigned int uiAllGridTotalWidth = static_cast<unsigned int>(iAllGridTotalRow + 1);
            unsigned int uiAllGridTotalHeight = static_cast<unsigned int>(iAllGridTotalColumn + 1);

            m_pUnderGrid->SetSize(uiAllGridTotalWidth, uiAllGridTotalHeight);
            m_ListTerrains = m_pMapLoader->LoadMapTerrain(*pMapWidget);
        }
        else
        {
            bLoadGameMapSuccessed = false;
        }
    }

    return bLoadGameMapSuccessed;
}
