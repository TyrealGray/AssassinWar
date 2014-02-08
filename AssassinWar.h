#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>

class QTimer;
class AssassinWar : public QMainWindow
{
    Q_OBJECT

public:
    AssassinWar(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~AssassinWar();

protected:
    void paintEvent(QPaintEvent *PaintEvent);

private:
    QTimer* m_pRepaintTimer;
};

#endif // ASSASSINWAR_H
