#ifndef CHOOSINGMAPDLG_H
#define CHOOSINGMAPDLG_H

#include <QDialog>
#include <QString>

class GameSetting;
class QComboBox;
class QStringList;
class ChoosingMapDlg : public QDialog
{
    Q_OBJECT

public:
    ChoosingMapDlg(QWidget *parent = 0);
    ~ChoosingMapDlg();

    bool initialize();

    bool updateMapList(const QStringList& mapList);

    QString getCurrentMap();

protected:
    void closeEvent(QCloseEvent *closeEvent);

signals:
    void createGame(QString strCurrntMapName);
    void cancelCreateGame();
private slots:
    void onBtnCreateGame();
private:
    QComboBox* m_pMapList;
    GameSetting* m_pGameSetting;
};

#endif // CHOOSINGMAPDLG_H
