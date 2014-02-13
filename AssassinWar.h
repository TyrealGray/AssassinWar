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

    void initMainWin();

protected:

    void mouseReleaseEvent(QMouseEvent *mouseEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void paintEvent(QPaintEvent *paintEvent);

private slots:

    void onButttonHost_();

private:
    QTimer* m_pRepaintTimer;
    MapLoader* m_pMapLoader;
    UnderGrid* m_pUnderGrid;
    QToolBar* m_pToolbar;
    ToolbarManager* m_pToolbarManager;
    QList<QLabel *> m_ListTerrains;
    bool m_bIsAWRun;
    QPixmap m_background;

    void initToolbarManager_();
    void initBackground_(const QString& strBackgroundImagePath);
    void initToolbar_();
    void initRepainter_();
    void initMapSystem_();
    bool runAW_();
    bool loadGameMap_(const QString& strMapPath);
};

#endif // ASSASSINWAR_H
