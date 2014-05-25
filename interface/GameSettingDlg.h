#ifndef CHOOSINGMAPDLG_H
#define CHOOSINGMAPDLG_H

#include <QDialog>
#include <QString>

class GameSetting;
class QComboBox;
class QStringList;
class QLineEdit;
class GameSettingDlg : public QDialog
{
    Q_OBJECT

public:
    GameSettingDlg(QWidget *parent = 0);
    ~GameSettingDlg();

    void initialize();

    void updateMapList(const QStringList& mapList);

    QString getPlayerName();

    QString getCurrentMap();

protected:
    void closeEvent(QCloseEvent *closeEvent);

signals:
    void createGame();
    void cancelCreateGame();

private slots:
    void onBtnCreateGame();

private:
    QLineEdit* m_pPlayerNameEdit;
    QComboBox* m_pMapList;
    GameSetting* m_pGameSetting;
};

#endif // CHOOSINGMAPDLG_H
