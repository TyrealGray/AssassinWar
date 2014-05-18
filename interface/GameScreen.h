#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QScrollArea>
#include <QList>

class QPainter;
class GameServer;
class GameModule;
class GameNetwork;
class GameScreen : public QScrollArea
{
    Q_OBJECT

public:
    GameScreen(const int &iWidth, const int &iHeight,
               QWidget *parent = 0);
    ~GameScreen();

    void initScreen();

    void initServer();

    void openScreen(const QString& strCurrntMapName);

    void connectRoom(const QString& strPlayerName, const QString& ipAddress);

    void closeScreen();

    int getScreenOffsetX()const;

    int getScreenOffsetY()const;

    void drawAllGameScreen(QPainter& painter);

signals:

    void screenOpened();

    void screenClosed();

protected:

    void mouseReleaseEvent(QMouseEvent *mouseEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent * keyEvent);

private slots:

    void gameRoomConnected();

private:
    GameModule* m_pGameModule;
    GameServer* m_pGameServer;
    GameNetwork* m_pGameNetwork;
    bool m_bIsScreenOpen;
    int m_iScreenWidth;
    int m_iScreenHeight;

    void initGameModule();
    void closeRoomConnect();
    void closeServer();
    bool loadGameMap(const QString& strCurrntMapName);
    void onMouseClick(QMouseEvent *mouseEvent);
    void onMouseLeft(QMouseEvent *mouseEvent);
    void onMouseRight(QMouseEvent *mouseEvent);
};

#endif // GAMESCREEN_H