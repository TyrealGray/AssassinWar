#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QMouseEvent>

#include <QToolTip>

#include "GameScreen.h"
#include "MapLoader.h"
#include "UnderGrid.h"
#include "MapManager.h"
#include "PixelCoordinateTransfer.h"

const int GRID_NUMBER_IS_ZERO = 0;

GameScreen::GameScreen(const int &iWidth, const int &iHeight,
                       QWidget *parent)
    : QScrollArea(parent),
      m_pRepaintTimer(NULL), m_pMapLoader(NULL), m_pUnderGrid(NULL),
      m_bIsScreenOpen(false),
      m_iScreenWidth(iWidth), m_iScreenHeight(iHeight)
{

}

GameScreen::~GameScreen()
{
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

void GameScreen::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if(m_bIsScreenOpen)
    {
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::instance().toGridX(mouseEvent->pos().x() + static_cast<float>(horizontalScrollBar()->value()));
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::instance().toGridY(mouseEvent->pos().y() + static_cast<float>(verticalScrollBar()->value()));

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
                QToolTip::showText(mouseEvent->pos(), strX + "     " + strY + "   UnHit  " + gridX + "      " + gridY);
            }
            else
            {
                QToolTip::showText(mouseEvent->pos(), strX + "     " + strY + "   Hit  " + gridX + "      " + gridY);
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

void GameScreen::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(m_bIsScreenOpen)
    {
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::instance().toGridX(mouseEvent->pos().x() + static_cast<float>(horizontalScrollBar()->value()));
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::instance().toGridY(mouseEvent->pos().y() + static_cast<float>(verticalScrollBar()->value()));

        QString strX, strY;
        strX.setNum(iCurClickedGridX);
        strY.setNum(iCurClickedGridY);
        QToolTip::showText(mouseEvent->pos(), strX + "     " + strY);
    }
    else
    {
        QScrollArea::mouseMoveEvent(mouseEvent);
    }
}

bool GameScreen::initScreen()
{
    bool bInitSuccessed = true;

    setMouseTracking(true);

    initMapSystem_();

    return bInitSuccessed;
}

bool GameScreen::openScreen(const QString& strCurrntMapName)
{

    bool bOpenScreenSuccessed = true;

    bOpenScreenSuccessed = loadGameMap_(strCurrntMapName);

    return (m_bIsScreenOpen = bOpenScreenSuccessed);

}

bool GameScreen::loadGameMap_(const QString& strCurrntMapName)
{
    bool bLoadGameMapSuccessed = true;

    QWidget* pMapWidget =  m_pMapLoader->loadMap(MapManager::instance().getMapPath(strCurrntMapName));
    if(NULL == pMapWidget)
    {
        bLoadGameMapSuccessed = false;
    }
    else
    {
        setWidget(pMapWidget);

        int iMapWidth = (pMapWidget->size().width() > size().width()) ? pMapWidget->size().width() : m_iScreenWidth;
        int iMapHeight = (pMapWidget->size().height() > size().height()) ? pMapWidget->size().height() : m_iScreenHeight;

        QSize mapSize(iMapWidth, iMapHeight);

        float fMapWidth = static_cast<float>(mapSize.width());
        float fMapHeight = static_cast<float>(mapSize.height());

        unsigned int iBottomRightGridColumnIndex = PixelCoordinateTransfer::instance().toGridX(fMapWidth);
        unsigned int iBottomRightGridRowIndex = PixelCoordinateTransfer::instance().toGridY(fMapHeight);

        if(GRID_NUMBER_IS_ZERO != iBottomRightGridRowIndex && GRID_NUMBER_IS_ZERO != iBottomRightGridColumnIndex)
        {
            unsigned int uiAllGridTotalWidth = static_cast<unsigned int>(iBottomRightGridColumnIndex + 1);
            unsigned int uiAllGridTotalHeight = static_cast<unsigned int>(iBottomRightGridRowIndex + 1);

            m_pUnderGrid->setSize(uiAllGridTotalWidth, uiAllGridTotalHeight);

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
            pMapWidget->setMouseTracking(true);
        }
        else
        {
            bLoadGameMapSuccessed = false;
        }
    }

    return bLoadGameMapSuccessed;
}

void GameScreen::initMapSystem_()
{
    m_pMapLoader = new MapLoader();
    m_pMapLoader->initMapLoader();

    m_pUnderGrid = new UnderGrid();
}