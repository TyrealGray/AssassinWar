#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>
#include <QList>

class QTimer;
class QLabel;
class UnderGrid;
class MapLoader;
class ToolbarManager;
class AssassinWar : public QMainWindow
{
    Q_OBJECT

public:

    AssassinWar(QWidget *parent = 0, Qt::WFlags flags = 0);

    ~AssassinWar();

    void InitMainWin();

protected:

    void paintEvent(QPaintEvent *paintEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

private:
    QTimer* m_pRepaintTimer;
    MapLoader* m_pMapLoader;
    UnderGrid* m_pUnderGrid;
    QToolBar* m_pToolbar;
    ToolbarManager* m_pToolbarManager;
    QList<QLabel *> m_ListTerrains;
    QPixmap m_background;

    void InitToolbarManager_();
    void InitBackground_();
    void InitToolbar_();
    bool initAW_();
    bool LoadGameMap_(const QString& strMapPath);
};

#endif // ASSASSINWAR_H
