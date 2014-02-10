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

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void paintEvent(QPaintEvent *paintEvent);

private slots:

    void OnButttonHost_();

private:
    QTimer* m_pRepaintTimer;
    MapLoader* m_pMapLoader;
    UnderGrid* m_pUnderGrid;
    QToolBar* m_pToolbar;
    ToolbarManager* m_pToolbarManager;
    QList<QLabel *> m_ListTerrains;
    bool m_bIsAWRun;
    QPixmap m_background;

    void InitToolbarManager_();
    void InitBackground_(const QString& strBackgroundImagePath);
    void InitToolbar_();
    void InitRepainter_();
    void InitMapSystem_();
    bool RunAW_();
    bool LoadGameMap_(const QString& strMapPath);
};

#endif // ASSASSINWAR_H
