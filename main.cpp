#include "AssassinWar.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication AW_App(argc, argv);
    AssassinWar AW;
    if(!AW.initAW())
    {
        //error
        AW_App.quit();
    }
    else
    {
        AW.show();
        return AW_App.exec();
    }

}
