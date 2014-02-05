/********************************************************************************
** Form generated from reading UI file 'AssassinWar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSASSINWAR_H
#define UI_ASSASSINWAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AssassinWarClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AssassinWarClass)
    {
        if (AssassinWarClass->objectName().isEmpty())
            AssassinWarClass->setObjectName(QString::fromUtf8("AssassinWarClass"));
        AssassinWarClass->resize(600, 400);
        menuBar = new QMenuBar(AssassinWarClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AssassinWarClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AssassinWarClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AssassinWarClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AssassinWarClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AssassinWarClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AssassinWarClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AssassinWarClass->setStatusBar(statusBar);

        retranslateUi(AssassinWarClass);

        QMetaObject::connectSlotsByName(AssassinWarClass);
    } // setupUi

    void retranslateUi(QMainWindow *AssassinWarClass)
    {
        AssassinWarClass->setWindowTitle(QApplication::translate("AssassinWarClass", "AssassinWar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AssassinWarClass: public Ui_AssassinWarClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSASSINWAR_H
