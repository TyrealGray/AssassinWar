#include <QTimer>
#include <QLabel>
#include <QAction>
#include <QPainter>
#include <QToolBar>
#include <QMouseEvent>

#include <QToolTip>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "MapLoader.h"
#include "UnderGrid.h"
#include "MapManager.h"
#include "ToolbarManager.h"
#include "PixelCoordinateTransfer.h"

const int GRID_NUMBER_IS_ZERO = 0;
const int ICON_SIZE = 45;
const int MAIN_WIN_WIDTH = 850;

std::shared_ptr<Grid> g_pGrid = NULL;

AssassinWar::AssassinWar(const int &iWidth, const int &iHeight,
                         QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL), m_pMapLoader(NULL), m_pUnderGrid(NULL), m_pToolbar(NULL), m_pToolbarManager(NULL),
      m_bIsAWRun(false),
      m_iScreenWidth(iWidth), m_iScreenHeight(iHeight)
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

void AssassinWar::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if(m_bIsAWRun)
    {
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::instance().toGridX(mouseEvent->pos().x());
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::instance().toGridY(mouseEvent->pos().y());

        QString strX, strY, gridX, gridY;
        strX.setNum(iCurClickedGridX);
        strY.setNum(iCurClickedGridY);

        std::shared_ptr<Grid> pCurClickGrid = m_pUnderGrid->getGrid(iCurClickedGridX, iCurClickedGridY);

        if(NULL != pCurClickGrid)
        {
            gridX.setNum(pCurClickGrid->getX());
            gridY.setNum(pCurClickGrid->getY());


            //mouse event click Terrians test code
            if(pCurClickGrid->isDisable())
            {
                QToolTip::showText(mouseEvent->pos(), "UnHit");
            }
            else
            {
                QToolTip::showText(mouseEvent->pos(), "Hit!!");
            }
            //test code end
        }
        else
        {
            //can not get the Grid infomation
        }
    }
    else
    {
        //do nothing
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

void AssassinWar::onButttonHost_()
{
    runAW_();

    setMouseTracking(false);
    m_pToolbar->setVisible(false);
}

bool AssassinWar::runAW_()
{
    bool bInitAWSuccessed = true;

    QString strMapPath = "./map/SmallTown.ui";
    bInitAWSuccessed = loadGameMap_(strMapPath);

    return (m_bIsAWRun = bInitAWSuccessed);
}

bool AssassinWar::loadGameMap_(const QString& strMapPath)
{
    bool bLoadGameMapSuccessed = true;

    QWidget* pMapWidget =  m_pMapLoader->loadMap(strMapPath);
    if(NULL == pMapWidget)
    {
        bLoadGameMapSuccessed = false;
    }
    else
    {
        setWindowState(Qt::WindowFullScreen);
        setCentralWidget(pMapWidget);

        int iMapWidth = (pMapWidget->size().width() > size().width()) ? pMapWidget->size().width() : size().width();
        int iMapHeight = (pMapWidget->size().height() > size().height()) ? pMapWidget->size().height() : size().height();

        QSize mapSize(iMapHeight, iMapWidth);

        float fMapWidth = static_cast<float>(mapSize.width());
        float fMapHeight = static_cast<float>(mapSize.height());

        unsigned int iBottomRightGridColumnIndex = PixelCoordinateTransfer::instance().toGridX(fMapWidth);
        unsigned int iBottomRightGridRowIndex = PixelCoordinateTransfer::instance().toGridY(fMapHeight);

        if(GRID_NUMBER_IS_ZERO != iBottomRightGridRowIndex && GRID_NUMBER_IS_ZERO != iBottomRightGridColumnIndex)
        {
            unsigned int uiAllGridTotalWidth = static_cast<unsigned int>(iBottomRightGridColumnIndex + 1);
            unsigned int uiAllGridTotalHeight = static_cast<unsigned int>(iBottomRightGridRowIndex + 1);

            m_pUnderGrid->setSize(uiAllGridTotalWidth, uiAllGridTotalHeight);

            //UNDONE change this API
            initBackground_("./Resources/SmallTown/Background/SmallTown.jpg");

            m_ListTerrains = m_pMapLoader->loadMapTerrain(*pMapWidget);

            for(unsigned int index = 0; index < m_ListTerrains.size(); ++index)
            {
                unsigned int iTerrainTopLX = PixelCoordinateTransfer::instance().toGridX(m_ListTerrains[index]->geometry().left());
                unsigned int iTerrainTopLY = PixelCoordinateTransfer::instance().toGridY(m_ListTerrains[index]->geometry().top());

                unsigned int iTerrainBottomRX = PixelCoordinateTransfer::instance().toGridX(m_ListTerrains[index]->geometry().right());
                unsigned int iTerrainBottomRY = PixelCoordinateTransfer::instance().toGridY(m_ListTerrains[index]->geometry().bottom());

                m_pUnderGrid->disableGrids(
                    iTerrainTopLX,
                    iTerrainTopLY,
                    iTerrainBottomRX,
                    iTerrainBottomRY
                );
            }
        }
        else
        {
            bLoadGameMapSuccessed = false;
        }
    }

    return bLoadGameMapSuccessed;
}

void AssassinWar::initMainWin()
{
    initToolbarManager_();

    initBackground_("./AssassinsWar.jpg");

    initToolbar_();

    initRepainter_();

    initMapSystem_();

    resize(MAIN_WIN_WIDTH, MAIN_WIN_WIDTH / 2);
    setMouseTracking(true);
}

void AssassinWar::initToolbar_()
{
    m_pToolbar = addToolBar(tr("MainToolbar"));
    m_pToolbar->addAction(m_pToolbarManager->getButtonHost());
    m_pToolbar->addAction(m_pToolbarManager->getButtonJoin());
    m_pToolbar->addAction(m_pToolbarManager->getButtonSearchGame());
    m_pToolbar->addAction(m_pToolbarManager->getButtonSetting());
    m_pToolbar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    m_pToolbar->setMovable(false);
    m_pToolbar->setVisible(false);

    connect(m_pToolbarManager->getButtonHost(), SIGNAL(triggered()), this, SLOT(onButttonHost_()));
}

void AssassinWar::initBackground_(const QString& strBackgroundImagePath)
{
    QImage background;
    background.load(strBackgroundImagePath);
    m_background = QPixmap::fromImage(background.scaled(size(), Qt::KeepAspectRatioByExpanding));
}

void AssassinWar::initToolbarManager_()
{
    m_pToolbarManager = new ToolbarManager();
    m_pToolbarManager->init();
}

void AssassinWar::initRepainter_()
{
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);
}

void AssassinWar::initMapSystem_()
{
    m_pMapLoader = new MapLoader();
    m_pMapLoader->initMapLoader();

    m_pUnderGrid = new UnderGrid();
}
