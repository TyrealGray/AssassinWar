#include <QTimer>
#include <QThread>

#include "GameServer.h"
#include "GameModule.h"
#include "GameServerService.h"

GameServer::GameServer(GameModule* gameModule, const QString& strCurrntMapName, QObject * parent /* = 0*/)
    : QTcpServer(parent),
      m_pGameUpdateTimer(NULL), m_pGameModule(gameModule), m_pGameUpdateThread(NULL),
      m_mapName(strCurrntMapName)
{
}


GameServer::~GameServer(void)
{
    close();
    m_pGameUpdateThread->quit();
    m_pGameUpdateThread->wait();
}

bool GameServer::hostServer()
{
    initGameUpdateThread();
    initGameModuleDataUpdateTimer();
    return listen(QHostAddress::Any, 8126);
}

void GameServer::incomingConnection(int socketID)
{
    GameServerService * pThread = new GameServerService(socketID, m_pGameModule, m_mapName, this);
    connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
    pThread->start();
}

void GameServer::initGameUpdateThread()
{
    m_pGameUpdateThread = new QThread(this);
    m_pGameUpdateThread->start();
}

void GameServer::initGameModuleDataUpdateTimer()
{
    m_pGameUpdateTimer = new QTimer();
    connect(m_pGameUpdateTimer, SIGNAL(timeout()), m_pGameModule, SLOT(updateCharactersStatus()));
    m_pGameUpdateTimer->start(200);

    m_pGameUpdateTimer->moveToThread(m_pGameUpdateThread);

    connect(m_pGameUpdateThread, SIGNAL(finished()), m_pGameUpdateTimer, SLOT(stop()));
    connect(m_pGameUpdateThread, SIGNAL(finished()), m_pGameUpdateTimer, SLOT(deleteLater()));
}