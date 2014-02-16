#ifndef ASSASSINWAR_H
#define ASSASSINWAR_H

#include <QtGui/QMainWindow>

class QTimer;
class GameScreen;
class ToolbarManager;
class ChoosingMapDlg;
class AssassinWar : public QMainWindow
{
    Q_OBJECT

public:

    AssassinWar(const int &iWidth, const int &iHeight,
                QWidget *parent = 0, Qt::WFlags flags = 0);

    ~AssassinWar();

    void initMainWin();

protected:

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void paintEvent(QPaintEvent *paintEvent);

private slots:

    void onButttonHost_();

    bool runAW_(const QString& strCurrntMapName);

    void showMainWin_();

private:
    QTimer* m_pRepaintTimer;
    QToolBar* m_pToolbar;
    GameScreen* m_pGameScreen;
    ToolbarManager* m_pToolbarManager;
    ChoosingMapDlg* m_pChoosingMapDlg;
    bool m_bIsAWRun;
    unsigned int m_iScreenWidth;
    unsigned int m_iScreenHeight;
    QPixmap m_background;

    void initGameScreen_();
    void initToolbarManager_();
    void initChoosingMapDlg_();
    void initBackground_(const QString& strBackgroundImagePath);
    void initToolbar_();
    void initRepainter_();
};

#endif // ASSASSINWAR_H
