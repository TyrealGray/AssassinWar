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

    void init(const QString& ipAddress);

    void setPlayerPos(const unsigned int &uiX, const unsigned int &uiY);

signals:

    void targetingLocalPlayer(int id);

    void characterDead(int id);

    void playerExpose(int id);

    void newCharacterShowUp(int id, unsigned int uiX, unsigned int uiY, int roleType);

private slots:

    void updateGame();

    void sendUpdateRequest();

private:
    QTimer* m_pUpdateTimer;
    GameModule* m_pGameModule;
    QString m_name;
    quint16 m_nextBlockSize;

    void initUpdateTimer();

    void sendUpdatePositionRequest();

    void connectToServer(const QString& ipAddress);

    bool isAvailablePackageSizeSmallThan(quint16 size);

};