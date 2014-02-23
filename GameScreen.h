#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QScrollArea>
#include <QList>

class QLabel;
class QPainter;
class UnderGrid;
class MapLoader;
class GameScreen : public QScrollArea
{
    Q_OBJECT

public:
    GameScreen(const int &iWidth, const int &iHeight,
               QWidget *parent = 0);
    ~GameScreen();

    bool initScreen();

    bool openScreen(const QString& strCurrntMapName);

    int getScreenOffsetX()const;

    int getScreenOffsetY()const;

    void drawAllGameScreen(QPainter& painter);

protected:

    void mouseReleaseEvent(QMouseEvent *mouseEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

private:
    MapLoader* m_pMapLoader;
    UnderGrid* m_pUnderGrid;
    bool m_bIsScreenOpen;
    int m_iScreenWidth;
    int m_iScreenHeight;
    QList<QLabel *> m_terrainsList;

    void initBackground_(const QString& strBackgroundImagePath);
    void initRepainter_();
    void initMapSystem_();
    bool loadGameMap_(const QString& strCurrntMapName);
    void setTerrainInvalidZone_();

};

#endif // GAMESCREEN_H