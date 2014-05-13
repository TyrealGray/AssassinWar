#pragma once

#include <QThread>
#include <QTcpSocket>

class GameModule;
class GameServerService : public QThread
{
    Q_OBJECT

public:
    GameServerService(int iSocketID, GameModule* gameModule, QObject *parent);
    ~GameServerService(void);

protected:
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private slots:
    void readInComeRequest();

private:
    QTcpSocket* m_pTcpSocket;
    GameModule* m_pGameModule;
    int m_iSocketID;
    quint16 m_nextBlockSize;

    void sendCharacterPositionData();

    bool isAvailablePackageSizeSmallThan(quint16 size);
};

