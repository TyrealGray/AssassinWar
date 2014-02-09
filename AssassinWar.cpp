#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QToolBar>
#include <QMouseEvent>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"
#include "UnderGrid.h"
#include "ToolbarManager.h"
#include "PixelCoordinateTransfer.h"

const int GRID_NUMBER_IS_ZERO = -1;
const int MAIN_TOOLBAR_POS = 45;

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL),
      m_pMapLoader(NULL),
      m_pUnderGrid(NULL),
      m_pToolbar(NULL),
      m_pToolbarManager(NULL)
{

}

AssassinWar::~AssassinWar()
{
    if(NULL != m_pRepaintTimer)
    {
        m_pRepaintTimer->stop();
    }

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

    if(NULL != m_pToolbarManager)
    {
        delete m_pToolbarManager;
        m_pToolbarManager = NULL;
    }
}

void AssassinWar::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(MAIN_TOOLBAR_POS > mouseEvent->pos().y())
    {
        m_pToolbar->setVisible(true);
    }
    else
    {
        m_pToolbar->setVisible(false);
    }
}

void AssassinWar::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, m_background);
}

bool AssassinWar::initAW_()
{
    bool bInitAWSuccessed = true;
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);

    m_pMapLoader = new MapLoader();
    m_pMapLoader->InitMapLoader();

    m_pUnderGrid = new UnderGrid();

    QString strMapPath = "./map/map1.ui";
    bInitAWSuccessed = LoadGameMap_(strMapPath);

    setWindowState(Qt::WindowFullScreen);

    return bInitAWSuccessed;
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

void AssassinWar::InitMainWin()
{
    InitToolbarManager_();

    InitBackground_();

    InitToolbar_();

    resize(640, 360);
    setMouseTracking(true);
}

void AssassinWar::InitToolbar_()
{
    m_pToolbar = addToolBar(tr("MainToolbar"));
    m_pToolbar->addAction(m_pToolbarManager->GetButtonHost());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonJoin());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonSearchGame());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonSetting());
    m_pToolbar->setIconSize(QSize(45, 45));
    m_pToolbar->setMovable(false);
    m_pToolbar->setVisible(false);
}

void AssassinWar::InitBackground_()
{
    QImage background;
    background.load("./AssassinsWar.jpg");
    m_background = QPixmap::fromImage(background.scaled(size(), Qt::KeepAspectRatio));
}

void AssassinWar::InitToolbarManager_()
{
    m_pToolbarManager = new ToolbarManager();
    m_pToolbarManager->Init();
}
