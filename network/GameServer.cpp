#include "GameServer.h"
#include "GameModule.h"
#include "GameServerService.h"

GameServer::GameServer(GameModule* gameModule, QObject * parent /* = 0*/)
    : QTcpServer(parent),
      m_pGameModule(gameModule)
{
}


GameServer::~GameServer(void)
{
}

bool GameServer::hostServer()
{
    return listen(QHostAddress::Any, 8126);
}

void GameServer::incomingConnection(int socketID)
{
    GameServerService * pThread = new GameServerService(socketID, m_pGameModule, this);
    connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
    pThread->start();
}