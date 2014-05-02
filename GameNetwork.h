#pragma once
#include <QTcpSocket>

class GameNetwork : public QTcpSocket
{
    Q_OBJECT

public:
    GameNetwork(const QString& name, QObject *parent = 0);
    ~GameNetwork(void);

    void setPlayerPos(const unsigned int &uiX, const unsigned int &uiY);

signals:

    void targetingLocalPlayer(int id);

    void characterDead(int id);

    void playerExpose(int id);

    void characterPositionChange(int id, unsigned int uiX, unsigned int uiY);

    void newCharacterShowUp(int id, unsigned int uiX, unsigned int uiY, int roleType);

private slots:

    void update();

private:
    QString m_name;
    unsigned short m_nextBlockSize;

    void connectToServer(const QString& ipAddress);

    bool isAvailablePackageSizeSmallThan(const unsigned int& uiSize);

};

