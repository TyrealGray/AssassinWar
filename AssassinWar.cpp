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

const int ICON_SIZE = 45;
const int MAIN_WIN_WIDTH = 850;
const QString BACKGROUND_IMG = "./AssassinWar.jpg";

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
        m_pGameScreen->drawAllGameScreen(painter);
    }
}


void AssassinWar::onButttonHost()
{
    setMouseTracking(false);
    m_pToolbar->setVisible(false);

    m_pChoosingMapDlg->updateMapList(MapManager::instance().getMapList());
    m_pChoosingMapDlg->show();

}

bool AssassinWar::runAW(const QString& strCurrntMapName)
{
    m_pChoosingMapDlg->hide();

    setWindowState(Qt::WindowFullScreen);

    initBackground(MapManager::instance().getMapBackground(strCurrntMapName));

    m_bIsAWRun = m_pGameScreen->openScreen(strCurrntMapName);

    return m_bIsAWRun ;
}

void AssassinWar::initMainWin()
{
    setWindowFlags(Qt::FramelessWindowHint);

    initGameScreen();

    initToolbarManager();

    initChoosingMapDlg();

    initToolbar();

    initRepainter();

    initBackground(BACKGROUND_IMG);

    showMainWin();
}

void AssassinWar::initToolbar()
{
    m_pToolbar = addToolBar(tr("MainToolbar"));
    m_pToolbar->addAction(m_pToolbarManager->getButtonHost());
    m_pToolbar->addAction(m_pToolbarManager->getButtonJoin());
    m_pToolbar->addAction(m_pToolbarManager->getButtonHelp());
    m_pToolbar->addAction(m_pToolbarManager->getButtonSetting());
    m_pToolbar->addAction(m_pToolbarManager->getButtonQuit());
    m_pToolbar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    m_pToolbar->setMovable(false);
    m_pToolbar->setVisible(false);

    connect(m_pToolbarManager->getButtonHost(), SIGNAL(triggered()), this, SLOT(onButttonHost()));
    connect(m_pToolbarManager->getButtonQuit(), SIGNAL(triggered()), this, SLOT(close()));
}

void AssassinWar::initBackground(const QString& strBackgroundImagePath)
{
    QImage background;
    background.load(strBackgroundImagePath);
    m_background = QPixmap::fromImage(background.scaled(size(), Qt::KeepAspectRatioByExpanding));
}

void AssassinWar::initToolbarManager()
{
    m_pToolbarManager = new ToolbarManager();
    m_pToolbarManager->initialize();
}

void AssassinWar::initRepainter()
{
    m_pRepaintTimer = new QTimer(this);
    connect(m_pRepaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_pRepaintTimer->start(200);
}

void AssassinWar::initChoosingMapDlg()
{
    m_pChoosingMapDlg = new ChoosingMapDlg(this);
    m_pChoosingMapDlg->initialize();
    connect(m_pChoosingMapDlg, SIGNAL(createGame(QString)), this, SLOT(runAW(QString)));
    connect(m_pChoosingMapDlg, SIGNAL(cancelCreateGame()), this, SLOT(showMainWin()));
}

void AssassinWar::initGameScreen()
{
    m_pGameScreen = new GameScreen(m_iScreenWidth, m_iScreenHeight);

    m_pGameScreen->initScreen();

    m_pGameScreen->setStyleSheet("background-color:transparent;");

    setCentralWidget(m_pGameScreen);
}

void AssassinWar::showMainWin()
{
    resize(MAIN_WIN_WIDTH, MAIN_WIN_WIDTH / 2);

    initBackground(BACKGROUND_IMG);

    setMouseTracking(true);
}