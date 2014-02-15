#include "AssassinWar.h"
#include <QtGui/QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication AW_App(argc, argv);
    int iWidth = QApplication::desktop()->width();
    int iHeight = QApplication::desktop()->height();
    AssassinWar AW(iWidth, iHeight);
    AW.initMainWin();
    AW.show();
    return AW_App.exec();
}
