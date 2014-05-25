#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>

class QTimer;
class GameScreen;
class ToolbarManager;
class GameSettingDlg;
class AssassinWar : public QMainWindow
{
    Q_OBJECT

public:

    AssassinWar(const int &iWidth, const int &iHeight,
                QWidget *parent = 0, Qt::WFlags flags = 0);

    ~AssassinWar();

    void initMainWin();

protected:

    void closeEvent(QCloseEvent *closeEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void paintEvent(QPaintEvent *paintEvent);

private slots:

    void gameRun();

    void gameClose();

    void onButttonHost();

    void hostGame();

    void showMainWin();

private:
    QTimer* m_pRepaintTimer;
    QToolBar* m_pToolbar;
    GameScreen* m_pGameScreen;
    ToolbarManager* m_pToolbarManager;
    GameSettingDlg* m_pGameSettingDlg;
    bool m_bIsAWRun;
    unsigned int m_iScreenWidth;
    unsigned int m_iScreenHeight;
    QPixmap m_background;

    void initGameScreen();
    void initToolbarManager();
    void initChoosingMapDlg();
    void initBackground(const QString& strBackgroundImagePath);
    void initToolbar();
    void initRepainter();
};

#endif // ASSASSINWAR_H
