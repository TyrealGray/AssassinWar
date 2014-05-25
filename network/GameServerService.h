#pragma once

#include <QThread>
#include <QTcpSocket>

class GameModule;
class GameServerService : public QThread
{
    Q_OBJECT

public:
    GameServerService(int iSocketID, GameModule* gameModule, const QString& currntMapName, QObject *parent);
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
    QString m_mapName;
    quint16 m_nextBlockSize;

    void sendCharacterPositionData();

    void sendMapName();

    bool isAvailablePackageSizeSmallThan(quint16 size);
};

