#include "AssassinWar.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AssassinWar w;
	w.show();
	return a.exec();
}
