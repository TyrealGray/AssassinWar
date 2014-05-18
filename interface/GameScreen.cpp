#include <QPainter>
#include <QScrollBar>
#include <QScrollArea>
#include <QMouseEvent>

#include "GameScreen.h"

#include "GameModule.h"
#include "GameServer.h"
#include "GameNetwork.h"

#include "MapManager.h"
#include "PixelCoordinateTransfer.h"

const int GRID_NUMBER_IS_ZERO = 0;
const int ENSURE_VISIBLE_BOUNDARY_DISTANCE = 250;

GameScreen::GameScreen(const int &iWidth, const int &iHeight,
                       QWidget *parent)
    : QScrollArea(parent),
      m_pGameModule(NULL), m_pGameServer(NULL), m_pGameNetwork(NULL),
      m_bIsScreenOpen(false),
      m_iScreenWidth(iWidth), m_iScreenHeight(iHeight)
{

}

GameScreen::~GameScreen()
{
    delete m_pGameModule;
    m_pGameModule = NULL;

    delete m_pGameServer;
    m_pGameServer = NULL;

    delete m_pGameNetwork;
    m_pGameNetwork = NULL;
}

void GameScreen::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    onMouseClick(mouseEvent);
}

void GameScreen::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(m_bIsScreenOpen)
    {
        unsigned int iCurClickedGridX = PixelCoordinateTransfer::toGrid(mouseEvent->pos().x() + getScreenOffsetX());
        unsigned int iCurClickedGridY = PixelCoordinateTransfer::toGrid(mouseEvent->pos().y() + getScreenOffsetY());
    }
    else
    {
        QScrollArea::mouseMoveEvent(mouseEvent);
    }
}

void GameScreen::keyPressEvent(QKeyEvent * keyEvent)
{
    if(m_bIsScreenOpen && Qt::Key_Escape == keyEvent->key())
    {
        emit screenClosed();
    }
    else
    {
        QScrollArea::keyPressEvent(keyEvent);
    }
}

void GameScreen::initScreen()
{
    setMouseTracking(true);

    horizontalScrollBar()->setVisible(false);
    verticalScrollBar()->setVisible(false);
}

void GameScreen::initServer()
{
    if(NULL == m_pGameModule)
    {
        initGameModule();
    }

    m_pGameServer = new GameServer(m_pGameModule, this);

    m_pGameServer->hostServer();
}

void GameScreen::initGameModule()
{
    m_pGameModule = new GameModule();

    m_pGameModule->init();
}

void GameScreen::openScreen(const QString& strCurrntMapName)
{
    m_bIsScreenOpen = loadGameMap(strCurrntMapName);
}

void GameScreen::connectRoom(const QString& strPlayerName, const QString& ipAddress)
{
    m_pGameNetwork = new GameNetwork(strPlayerName, m_pGameModule, this);

    connect(m_pGameNetwork, SIGNAL(networkConnected()), this, SLOT(gameRoomConnected()));

    m_pGameNetwork->connectRoomIP(ipAddress);
}

void GameScreen::gameRoomConnected()
{
    emit screenOpened();
}

void GameScreen::closeScreen()
{
    closeRoomConnect();

    closeServer();

    QWidget* pCurrentWid = this->widget();

    this->setWidget(NULL);

    if(NULL != pCurrentWid)
    {
        pCurrentWid->setMouseTracking(false);

        delete pCurrentWid;
    }

    m_bIsScreenOpen = false;
}

void GameScreen::closeRoomConnect()
{
    m_pGameNetwork->close();

    m_pGameNetwork->deleteLater();

    m_pGameNetwork = NULL;
}

void GameScreen::closeServer()
{
    m_pGameServer->close();

    m_pGameServer->deleteLater();

    m_pGameServer = NULL;
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
    //int iPlayerX = PixelCoordinateTransfer::toPixel(m_pGameModule->getPlayerGridX());
    //int iPlayerY = PixelCoordinateTransfer::toPixel(m_pGameModule->getPlayerGridY());
    //ensureVisible(iPlayerX, iPlayerY, ENSURE_VISIBLE_BOUNDARY_DISTANCE, ENSURE_VISIBLE_BOUNDARY_DISTANCE);
    m_pGameModule->drawAllCharacter(painter, getScreenOffsetX(), getScreenOffsetY());
}

bool GameScreen::loadGameMap(const QString& strCurrntMapName)
{
    bool bLoadGameMapSuccessed = false;

    QWidget* pMapWidget =  m_pGameModule->loadMap(MapManager::instance().getMapPath(strCurrntMapName));
    if(NULL != pMapWidget)
    {
        setWidget(pMapWidget);

        int iMapWidth = (pMapWidget->size().width() > size().width()) ? pMapWidget->size().width() : m_iScreenWidth;
        int iMapHeight = (pMapWidget->size().height() > size().height()) ? pMapWidget->size().height() : m_iScreenHeight;

        unsigned int iBottomRightGridColumnIndex = PixelCoordinateTransfer::toGrid(iMapWidth);
        unsigned int iBottomRightGridRowIndex = PixelCoordinateTransfer::toGrid(iMapHeight);

        if(GRID_NUMBER_IS_ZERO != iBottomRightGridRowIndex && GRID_NUMBER_IS_ZERO != iBottomRightGridColumnIndex)
        {

            m_pGameModule->setMapSize(iBottomRightGridColumnIndex + 1, iBottomRightGridRowIndex + 1);

            m_pGameModule->loadMapTerrain();

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

void GameScreen::onMouseClick(QMouseEvent *mouseEvent)
{
    if(m_bIsScreenOpen)
    {
        if(Qt::RightButton == mouseEvent->button())
        {
            onMouseRight(mouseEvent);
        }
        else if(Qt::LeftButton == mouseEvent->button())
        {
            onMouseLeft(mouseEvent);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        //do nothing
    }
}

void GameScreen::onMouseLeft(QMouseEvent *mouseEvent)
{

}

void GameScreen::onMouseRight(QMouseEvent *mouseEvent)
{
    unsigned int iCurClickedGridX = PixelCoordinateTransfer::toGrid(mouseEvent->pos().x() + getScreenOffsetX());
    unsigned int iCurClickedGridY = PixelCoordinateTransfer::toGrid(mouseEvent->pos().y() + getScreenOffsetY());

    m_pGameNetwork->setPlayerPos(iCurClickedGridX, iCurClickedGridY);

}