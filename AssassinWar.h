#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>

class QTimer;
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
};

#endif // ASSASSINWAR_H
