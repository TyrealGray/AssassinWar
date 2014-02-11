#pragma once

class QAction;
class ToolbarManager
{
public:
    ToolbarManager(void);
    ~ToolbarManager(void);

    void init();

    QAction* getButtonHost();

    QAction* getButtonJoin();

    QAction* getButtonSearchGame();

    QAction* getButtonSetting();

private:
    QAction* m_pOnButtonHostAction;
    QAction* m_pOnButtonJoinAction;
    QAction* m_pOnButtonSearchGameAction;
    QAction* m_pOnButtonSetttingAction;

    void initToolbarAction_();
};

