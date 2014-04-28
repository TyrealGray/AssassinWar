#include <QLabel>
#include <QPainter>
#include <QScrollBar>
#include <QScrollArea>
#include <QMouseEvent>

#include <QToolTip>

#include "GameScreen.h"
#include "MapLoader.h"
#include "UnderGrid.h"
#include "MapManager.h"
#include "PixelCoordinateTransfer.h"

#include "CharacterManager.h"

const bool GAME_OVER = false;
const int GRID_NUMBER_IS_ZERO = 0;
const int ENSURE_VISIBLE_BOUNDARY_DISTANCE = 250;

GameScreen::GameScreen(const int &iWidth, const int &iHeight,
                       QWidget *parent)
    : QScrollArea(parent),
      m_pMapLoader(NULL), m_pUnderGrid(NULL), m_pCharacterManager(NULL),
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

    if(NULL != m_pCharacterManager)
    {
        delete m_pCharacterManager;
        m_pCharacterManager = NULL;
    }
}

void GameScreen::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if(m_bIsScreenOpen)
    {
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::toGrid(mouseEvent->pos().x() + getScreenOffsetX());
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::toGrid(mouseEvent->pos().y() + getScreenOffsetY());

        QString strX, strY, gridX, gridY;
        strX.setNum(iCurClickedGridX);
        strY.setNum(iCurClickedGridY);

        std::shared_ptr<Grid> pCurClickGrid = m_pUnderGrid->getGrid(iCurClickedGridX, iCurClickedGridY);

        if(NULL != pCurClickGrid)
        {
            gridX.setNum(pCurClickGrid->getX());
            gridY.setNum(pCurClickGrid->getY());

            if(pCurClickGrid->isAble() && Qt::RightButton == mouseEvent->button())
            {
                QToolTip::showText(mouseEvent->pos(), strX + "     " + strY + "   UnHit  " + gridX + "      " + gridY);
                m_pCharacterManager->setPlayerPos(pCurClickGrid->getX(), pCurClickGrid->getY());
            }
            else
            {
                QToolTip::showText(mouseEvent->pos(), strX + "     " + strY + "   Hit  " + gridX + "      " + gridY);
            }
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
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::toGrid(mouseEvent->pos().x() + getScreenOffsetX());
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::toGrid(mouseEvent->pos().y() + getScreenOffsetY());

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

void GameScreen::initScreen()
{
    setMouseTracking(true);

    initMapSystem();

    initCharacterManager();
}

bool GameScreen::openScreen(const QString& strCurrntMapName)
{

    m_bIsScreenOpen = loadGameMap(strCurrntMapName);

    return m_bIsScreenOpen ;
}

bool GameScreen::closeScreen()
{
    QWidget* pCurrentWid = this->widget();

    this->setWidget(NULL);

    if(NULL != pCurrentWid)
    {
        pCurrentWid->setMouseTracking(false);

        delete pCurrentWid;
    }

    m_bIsScreenOpen = false;

    return GAME_OVER;
}

int GameScreen::getScreenOffsetX()const
{
    return horizontalScrollBar()->value();
}

int GameScreen::getScreenOffsetY()const
{
    return verticalScrollBar()->value();
}

void GameScreen::drawAllGameScreen(QPainter& painter)
{
    int iPlayerX = PixelCoordinateTransfer::toPixel(m_pCharacterManager->getPlayerGridX());
    int iPlayerY = PixelCoordinateTransfer::toPixel(m_pCharacterManager->getPlayerGridY());
    ensureVisible(iPlayerX, iPlayerY, ENSURE_VISIBLE_BOUNDARY_DISTANCE, ENSURE_VISIBLE_BOUNDARY_DISTANCE);
    m_pCharacterManager->drawAllCharacter(painter, getScreenOffsetX(), getScreenOffsetY());
}

bool GameScreen::loadGameMap(const QString& strCurrntMapName)
{
    bool bLoadGameMapSuccessed = false;

    QWidget* pMapWidget =  m_pMapLoader->loadMap(MapManager::instance().getMapPath(strCurrntMapName));
    if(NULL != pMapWidget)
    {
        setWidget(pMapWidget);

        int iMapWidth = (pMapWidget->size().width() > size().width()) ? pMapWidget->size().width() : m_iScreenWidth;
        int iMapHeight = (pMapWidget->size().height() > size().height()) ? pMapWidget->size().height() : m_iScreenHeight;

        unsigned int iBottomRightGridColumnIndex = PixelCoordinateTransfer::toGrid(iMapWidth);
        unsigned int iBottomRightGridRowIndex = PixelCoordinateTransfer::toGrid(iMapHeight);

        if(GRID_NUMBER_IS_ZERO != iBottomRightGridRowIndex && GRID_NUMBER_IS_ZERO != iBottomRightGridColumnIndex)
        {
            unsigned int uiAllGridTotalWidth = iBottomRightGridColumnIndex + 1;
            unsigned int uiAllGridTotalHeight = iBottomRightGridRowIndex + 1;

            m_pUnderGrid->setSize(uiAllGridTotalWidth, uiAllGridTotalHeight);

            m_terrainsList = m_pMapLoader->loadMapTerrain(*pMapWidget);

            setTerrainInvalidZone();

            pMapWidget->setMouseTracking(true);

            bLoadGameMapSuccessed = true;
        }
    }
    else
    {
        //do nothing
    }

    return bLoadGameMapSuccessed;
}

void GameScreen::initMapSystem()
{
    m_pMapLoader = new MapLoader();
    m_pMapLoader->initMapLoader();

    m_pUnderGrid = new UnderGrid();

    horizontalScrollBar()->setVisible(false);
    verticalScrollBar()->setVisible(false);
}

void GameScreen::initCharacterManager()
{
    m_pCharacterManager = new CharacterManager();
    m_pCharacterManager->addPlayer();
}

void GameScreen::setTerrainInvalidZone()
{
    for(unsigned int index = 0; index < m_terrainsList.size(); ++index)
    {
        unsigned int iTerrainTopLX = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().left());
        unsigned int iTerrainTopLY = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().top());

        unsigned int iTerrainBottomRX = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().right());
        unsigned int iTerrainBottomRY = PixelCoordinateTransfer::toGrid(m_terrainsList[index]->geometry().bottom());

        m_pUnderGrid->disableGrids(
            iTerrainTopLX,
            iTerrainTopLY,
            iTerrainBottomRX,
            iTerrainBottomRY
        );
    }
}
