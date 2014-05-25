#ifndef JOINGAMEDLG_H
#define JOINGAMEDLG_H

#include <QDialog>

class QLineEdit;
class JoinGameDlg : public QDialog
{
    Q_OBJECT

public:
    JoinGameDlg(QWidget *parent = 0);
    ~JoinGameDlg();

    void initialize();

    QString getPlayerName();

    QString getHostServerIPAddress();

protected:
    void closeEvent(QCloseEvent *closeEvent);

signals:
    void joinGame();
    void cancelJoinGame();

private slots:
    void onBtnJoinGame();

private:
    QLineEdit* m_pPlayerNameEdit;
    QLineEdit* m_pIPAddressEdit;
};

#endif // JOINGAMEDLG_H
