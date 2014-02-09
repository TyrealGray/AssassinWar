#pragma once

class QAction;
class ToolbarManager
{
public:
    ToolbarManager(void);
    ~ToolbarManager(void);

    void Init();

    QAction* GetButtonHost();

    QAction* GetButtonJoin();

    QAction* GetButtonSearchGame();

    QAction* GetButtonSetting();

private:
    QAction* m_pOnButtonHostAction;
    QAction* m_pOnButtonJoinAction;
    QAction* m_pOnButtonSearchGameAction;
    QAction* m_pOnButtonSetttingAction;

    void InitToolbarAction_();
};

