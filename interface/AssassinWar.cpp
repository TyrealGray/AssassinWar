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
#include "GameSettingDlg.h"
#include "JoinGameDlg.h"

const int ICON_SIZE = 45;
const int MAIN_WIN_WIDTH = 850;
const QString BACKGROUND_IMG = "./AssassinWar.jpg";

AssassinWar::AssassinWar(const int &iWidth, const int &iHeight,
                         QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_pRepaintTimer(NULL), m_pToolbar(NULL), m_pGameScreen(NULL),
      m_pToolbarManager(NULL), m_pGameSettingDlg(NULL), m_pJoinGameDlg(NULL),
      m_bIsAWRun(false),
      m_iScreenWidth(iWidth), m_iScreenHeight(iHeight)
{

}

AssassinWar::~AssassinWar()
{
    delete m_pGameScreen;
    m_pGameScreen = NULL;


    if(NULL != m_pRepaintTimer)
    {
        m_pRepaintTimer->stop();
    }

    delete m_pToolbarManager;
    m_pToolbarManager = NULL;

}

void AssassinWar::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->accept();
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

    if(m_bIsAWRun && NULL != m_pGameScreen)
    {
        m_pGameScreen->drawGameScreen(painter);
    }
}

void AssassinWar::onButttonHost()
{
    setMouseTracking(false);
    m_pToolbar->setVisible(false);

    m_pGameSettingDlg->updateMapList(MapManager::instance().getMapList());
    m_pGameSettingDlg->show();
}

void AssassinWar::onButtonJoin()
{
    setMouseTracking(false);
    m_pToolbar->setVisible(false);

    m_pJoinGameDlg->show();
}

void AssassinWar::hostGame()
{
    m_pGameSettingDlg->hide();

    m_pGameScreen->initServer(m_pGameSettingDlg->getCurrentMap());

    m_pGameScreen->connectRoom(m_pGameSettingDlg->getPlayerName(), "127.0.0.1");
}

void AssassinWar::joinGame()
{
    m_pJoinGameDlg->hide();

    m_pGameScreen->connectRoom(m_pJoinGameDlg->getPlayerName(), m_pJoinGameDlg->getHostServerIPAddress());
}

void AssassinWar::initMainWin()
{
    setWindowFlags(Qt::FramelessWindowHint);

    initGameScreen();

    initToolbarManager();

    initGameSettingDlg();

    initJoinGameDlg();

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
    connect(m_pToolbarManager->getButtonJoin(), SIGNAL(triggered()), this, SLOT(onButtonJoin()));
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

void AssassinWar::initGameSettingDlg()
{
    m_pGameSettingDlg = new GameSettingDlg(this);
    m_pGameSettingDlg->initialize();
    connect(m_pGameSettingDlg, SIGNAL(createGame()), this, SLOT(hostGame()));
    connect(m_pGameSettingDlg, SIGNAL(cancelCreateGame()), this, SLOT(showMainWin()));
}

void AssassinWar::initJoinGameDlg()
{
    m_pJoinGameDlg = new JoinGameDlg(this);
    m_pJoinGameDlg->initialize();
    connect(m_pJoinGameDlg, SIGNAL(joinGame()), this, SLOT(joinGame()));
    connect(m_pJoinGameDlg, SIGNAL(cancelJoinGame()), this, SLOT(showMainWin()));
}

void AssassinWar::initGameScreen()
{
    m_pGameScreen = new GameScreen(m_iScreenWidth, m_iScreenHeight);

    m_pGameScreen->initScreen();

    m_pGameScreen->initGameModule();

    m_pGameScreen->setStyleSheet("background-color:transparent;");

    setCentralWidget(m_pGameScreen);

    connect(m_pGameScreen, SIGNAL(screenOpened()), this, SLOT(gameRun()));
    connect(m_pGameScreen, SIGNAL(screenClosed()), this, SLOT(gameClose()));
}

void AssassinWar::gameRun()
{
    setWindowState(Qt::WindowFullScreen);

    initBackground(MapManager::instance().getMapBackground(m_pGameScreen->getMapName()));

    m_bIsAWRun = true;
}

void AssassinWar::gameClose()
{
    m_pGameScreen->closeScreen();

    showMainWin();

    m_bIsAWRun = false;
}

void AssassinWar::showMainWin()
{
    resize(MAIN_WIN_WIDTH, MAIN_WIN_WIDTH / 2);

    initBackground(BACKGROUND_IMG);

    move((m_iScreenWidth - MAIN_WIN_WIDTH) / 2, (m_iScreenHeight - (MAIN_WIN_WIDTH / 2)) / 2);

    setMouseTracking(true);
}