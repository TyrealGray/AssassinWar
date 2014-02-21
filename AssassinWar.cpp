#include <QTimer>
#include <QAction>
#include <QPainter>
#include <QToolBar>
#include <QMouseEvent>

#include "CommentLib.h"

#include "AssassinWar.h"
#include "GameScreen.h"
#include "MapManager.h"
#include "ToolbarManager.h"
#include "ChoosingMapDlg.h"
#include "CharacterManager.h"
#include "PixelCoordinateTransfer.h"

const int ICON_SIZE = 45;
const int MAIN_WIN_WIDTH = 850;
const int ENSURE_VISIBLE_BOUNDARY_DISTANCE = 500;

AssassinWar::AssassinWar(const int &iWidth, const int &iHeight,
                         QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL), m_pToolbar(NULL), m_pGameScreen(NULL),
      m_pToolbarManager(NULL), m_pChoosingMapDlg(NULL),
      m_bIsAWRun(false),
      m_iScreenWidth(iWidth), m_iScreenHeight(iHeight)
{

}

AssassinWar::~AssassinWar()
{
    if(NULL != m_pGameScreen)
    {
        delete m_pGameScreen;
        m_pGameScreen = NULL;
    }

    if(NULL != m_pRepaintTimer)
    {
        m_pRepaintTimer->stop();
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

    if(m_bIsAWRun)
    {
        int iPlayerX = PixelCoordinateTransfer::instance().gridXToPixelCoordinateX(CharacterManager::instance().getPlayerCharacterGridX());
        int iPlayerY = PixelCoordinateTransfer::instance().gridYToPixelCoordinateY(CharacterManager::instance().getPlayerCharacterGridY());
        m_pGameScreen->ensureVisible(iPlayerX, iPlayerY, ENSURE_VISIBLE_BOUNDARY_DISTANCE, ENSURE_VISIBLE_BOUNDARY_DISTANCE);
        CharacterManager::instance().drawAllCharacter(painter, m_pGameScreen->getScreenOffsetX(), m_pGameScreen->getScreenOffsetY());
    }
}


void AssassinWar::onButttonHost_()
{
    setMouseTracking(false);
    m_pToolbar->setVisible(false);

    m_pChoosingMapDlg->updateMapList(MapManager::instance().getMapList());
    m_pChoosingMapDlg->show();

}

bool AssassinWar::runAW_(const QString& strCurrntMapName)
{
    m_pChoosingMapDlg->hide();

    setWindowState(Qt::WindowFullScreen);

    initBackground_(MapManager::instance().getMapBackground(strCurrntMapName));

    m_bIsAWRun = m_pGameScreen->openScreen(strCurrntMapName);

    return m_bIsAWRun ;
}

void AssassinWar::initMainWin()
{
    setWindowFlags(Qt::FramelessWindowHint);

    initGameScreen_();

    initToolbarManager_();

    initChoosingMapDlg_();

    initToolbar_();

    initRepainter_();

    initBackground_("./AssassinsWar.jpg");

    showMainWin_();
}

void AssassinWar::initToolbar_()
{
    m_pToolbar = addToolBar(tr("MainToolbar"));
    m_pToolbar->addAction(m_pToolbarManager->getButtonHost());
    m_pToolbar->addAction(m_pToolbarManager->getButtonJoin());
    m_pToolbar->addAction(m_pToolbarManager->getButtonHelp());
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
    m_pToolbarManager->initialize();
}

void AssassinWar::initRepainter_()
{
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(250);
}

void AssassinWar::initChoosingMapDlg_()
{
    m_pChoosingMapDlg = new ChoosingMapDlg(this);
    m_pChoosingMapDlg->initialize();
    connect(m_pChoosingMapDlg, SIGNAL(createGame(QString)), this, SLOT(runAW_(QString)));
    connect(m_pChoosingMapDlg, SIGNAL(cancelCreateGame()), this, SLOT(showMainWin_()));
}

void AssassinWar::showMainWin_()
{
    resize(MAIN_WIN_WIDTH, MAIN_WIN_WIDTH / 2);

    initBackground_("./AssassinsWar.jpg");

    setMouseTracking(true);
}

void AssassinWar::initGameScreen_()
{
    m_pGameScreen = new GameScreen(m_iScreenWidth, m_iScreenHeight);

    m_pGameScreen->initScreen();

    m_pGameScreen->setStyleSheet("background-color:transparent;");

    setCentralWidget(m_pGameScreen);
}
