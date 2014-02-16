#include <QAction>

#include "ToolbarManager.h"


ToolbarManager::ToolbarManager(void)
{
}


ToolbarManager::~ToolbarManager(void)
{
}

void ToolbarManager::initialize()
{
    initToolbarAction_();
}

QAction* ToolbarManager::getButtonHost()
{
    return m_pOnButtonHostAction;
}

QAction* ToolbarManager::getButtonJoin()
{
    return m_pOnButtonJoinAction;
}

QAction* ToolbarManager::getButtonSearchGame()
{
    return m_pOnButtonSearchGameAction;
}

QAction* ToolbarManager::getButtonSetting()
{
    return m_pOnButtonSetttingAction;
}

void ToolbarManager::initToolbarAction_()
{
    m_pOnButtonHostAction = new QAction(QObject::tr("Host a Game"), NULL);
    m_pOnButtonHostAction->setToolTip(QObject::tr("Host a Game"));
    m_pOnButtonHostAction->setIcon(QIcon("./Resources/Toolbar/Host.jpg"));

    m_pOnButtonJoinAction = new QAction(QObject::tr("Join a Game"), NULL);
    m_pOnButtonJoinAction->setToolTip(QObject::tr("Join a Game"));
    m_pOnButtonJoinAction->setIcon(QIcon("./Resources/Toolbar/Join.jpg"));

    m_pOnButtonSearchGameAction = new QAction(QObject::tr("Search Game"), NULL);
    m_pOnButtonSearchGameAction->setToolTip(QObject::tr("Search Game"));
    m_pOnButtonSearchGameAction->setIcon(QIcon("./Resources/Toolbar/SearchGame.jpg"));

    m_pOnButtonSetttingAction = new QAction(QObject::tr("Setting"), NULL);
    m_pOnButtonSetttingAction->setToolTip(QObject::tr("Setting"));
    m_pOnButtonSetttingAction->setIcon(QIcon("./Resources/Toolbar/Setting.jpg"));
}