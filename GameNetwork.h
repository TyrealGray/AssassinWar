#pragma once
#include <QTcpSocket>

class QTimer;
class GameModule;
class GameNetwork : public QTcpSocket
{
    Q_OBJECT

public:
    GameNetwork(const QString& name, GameModule* gameModule, QObject *parent = 0);
    ~GameNetwork(void);

    void connectRoomIP(const QString& ipAddress);

    void addPlayer();

    void setPlayerPos(const unsigned int &uiX, const unsigned int &uiY);

signals:

    void networkConnected();

private slots:

    void updateGame();

    void initNetworkRequest();

    void sendUpdateRequest();

private:
    QTimer* m_pUpdateTimer;
    GameModule* m_pGameModule;
    bool m_bIsInit;
    QString m_name;
    quint16 m_nextBlockSize;

    void initUpdateTimer();

    void sendUpdatePositionRequest();

    void connectToServer(const QString& ipAddress);

    bool isAvailablePackageSizeSmallThan(quint16 size);

};