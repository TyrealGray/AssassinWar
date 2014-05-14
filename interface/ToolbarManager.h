#pragma once

class QAction;
class ToolbarManager
{
public:
    ToolbarManager(void);
    ~ToolbarManager(void);

    void initialize();

    QAction* getButtonHost();

    QAction* getButtonJoin();

    QAction* getButtonHelp();

    QAction* getButtonSetting();

    QAction* getButtonQuit();

private:
    QAction* m_pOnButtonHostAction;
    QAction* m_pOnButtonJoinAction;
    QAction* m_pOnButtonHelpAction;
    QAction* m_pOnButtonSetttingAction;
    QAction* m_pOnButtonQuitAction;

    void initToolbarAction();
};

