#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>
#include <QList>

class QTimer;
class QLabel;
class UnderGrid;
class MapLoader;
class AssassinWar : public QMainWindow
{
    Q_OBJECT

public:
    AssassinWar(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~AssassinWar();

    bool initAW();

protected:
    void paintEvent(QPaintEvent *PaintEvent);

private:
    QTimer* m_pRepaintTimer;
    MapLoader* m_pMapLoader;
    UnderGrid* m_pUnderGrid;
    QList<QLabel *> m_ListTerrains;

    bool LoadGameMap_(const QString& strMapPath);
};

#endif // ASSASSINWAR_H
