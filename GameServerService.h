#pragma once

#include <QTcpSocket>

class GameModule;
class GameServerService : public QTcpSocket
{
    Q_OBJECT

public:
    GameServerService(GameModule* gameModule, QObject *parent);
    ~GameServerService(void);

private slots:
    void readInComeRequest();

private:
    GameModule* m_pGameModule;
    quint16 m_nextBlockSize;

    void sendCharacterPositionData();

    bool isAvailablePackageSizeSmallThan(quint16 size);
};

