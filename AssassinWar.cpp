#include <QTimer>
#include <QLabel>
#include <QAction>
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
const int ICON_SIZE = 45;
const int MAIN_WIN_WIDTH = 850;

AssassinWar::AssassinWar(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL),
      m_pMapLoader(NULL),
      m_pUnderGrid(NULL),
      m_pToolbar(NULL),
      m_pToolbarManager(NULL),
      m_bIsAWRun(false)
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
    if(ICON_SIZE > mouseEvent->pos().y() && !m_bIsAWRun)
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

void AssassinWar::OnButttonHost_()
{
    RunAW_();

    setMouseTracking(false);
    m_pToolbar->setVisible(false);
}

bool AssassinWar::RunAW_()
{
    setWindowState(Qt::WindowFullScreen);
    bool bInitAWSuccessed = true;

    QString strMapPath = "./map/SmallTown.ui";
    bInitAWSuccessed = LoadGameMap_(strMapPath);

    return (m_bIsAWRun = bInitAWSuccessed);
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

            //UNDONE change this API
            InitBackground_("./Resources/SmallTown/Background/SmallTown.jpg");

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

    InitBackground_("./AssassinsWar.jpg");

    InitToolbar_();

    InitRepainter_();

    InitMapSystem_();

    resize(MAIN_WIN_WIDTH, MAIN_WIN_WIDTH / 2);
    setMouseTracking(true);
}

void AssassinWar::InitToolbar_()
{
    m_pToolbar = addToolBar(tr("MainToolbar"));
    m_pToolbar->addAction(m_pToolbarManager->GetButtonHost());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonJoin());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonSearchGame());
    m_pToolbar->addAction(m_pToolbarManager->GetButtonSetting());
    m_pToolbar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    m_pToolbar->setMovable(false);
    m_pToolbar->setVisible(false);

    connect(m_pToolbarManager->GetButtonHost(), SIGNAL(triggered()), this, SLOT(OnButttonHost_()));
}

void AssassinWar::InitBackground_(const QString& strBackgroundImagePath)
{
    QImage background;
    background.load(strBackgroundImagePath);
    m_background = QPixmap::fromImage(background.scaled(size(), Qt::KeepAspectRatioByExpanding));
}

void AssassinWar::InitToolbarManager_()
{
    m_pToolbarManager = new ToolbarManager();
    m_pToolbarManager->Init();
}

void AssassinWar::InitRepainter_()
{
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);
}

void AssassinWar::InitMapSystem_()
{
    m_pMapLoader = new MapLoader();
    m_pMapLoader->InitMapLoader();

    m_pUnderGrid = new UnderGrid();
}
