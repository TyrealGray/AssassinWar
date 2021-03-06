#pragma once
#include <QTcpServer>


class QTimer;
class QThread;
class GameModule;
class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    GameServer(GameModule* gameModule, const QString& strCurrntMapName, QObject * parent = 0);
    ~GameServer(void);

    bool hostServer();

protected:
    void incomingConnection(int socketID);

private:
    QTimer* m_pGameUpdateTimer;
    QTimer* m_pNpcRandomWalkTimer;
    GameModule* m_pGameModule;
    QThread* m_pGameUpdateThread;
    QString m_mapName;

    void initGameUpdateThread();
    void initGameModuleDataUpdateTimer();
};

