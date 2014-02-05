#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>
#include "ui_AssassinWar.h"

class AssassinWar : public QMainWindow
{
	Q_OBJECT

public:
	AssassinWar(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AssassinWar();

private:
	Ui::AssassinWarClass ui;
};

#endif // ASSASSINWAR_H
