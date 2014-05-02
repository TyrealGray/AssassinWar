#include "GameServer.h"


GameServer::GameServer(QObject * parent /* = 0*/)
    : QTcpServer(parent)
{
}


GameServer::~GameServer(void)
{
}
