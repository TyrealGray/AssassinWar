#pragma once
#include <QTcpServer>

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    GameServer(QObject * parent = 0);
    ~GameServer(void);
};

