#pragma once
#include <QTcpServer>

class GameModule;
class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    GameServer(GameModule* gameModule, QObject * parent = 0);
    ~GameServer(void);

    bool hostServer();

protected:
    void incomingConnection(int socketID);

private:
    GameModule* m_pGameModule;
};

