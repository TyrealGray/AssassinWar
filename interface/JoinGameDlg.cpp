#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "JoinGameDlg.h"

JoinGameDlg::JoinGameDlg(QWidget *parent)
    : QDialog(parent),
      m_pPlayerNameEdit(NULL), m_pIPAddressEdit(NULL)
{

}

JoinGameDlg::~JoinGameDlg()
{
}

void JoinGameDlg::initialize()
{
    QVBoxLayout* pDlgLayout = new QVBoxLayout;

    QHBoxLayout* pDlgBtnLayout = new QHBoxLayout;
    QHBoxLayout* pPlayerNameEditLayout = new QHBoxLayout;
    QHBoxLayout* pIPAddressLayout = new QHBoxLayout;

    QLabel* pPlayerEditLabel = new QLabel(tr("Name: "));
    m_pPlayerNameEdit = new QLineEdit();
    pPlayerNameEditLayout->addWidget(pPlayerEditLabel);
    pPlayerNameEditLayout->addWidget(m_pPlayerNameEdit);
    pPlayerNameEditLayout->addStretch();

    QLabel* pMapListLabel = new QLabel(tr("input host server IP address: "));
    m_pIPAddressEdit = new QLineEdit();
    pIPAddressLayout->addWidget(pMapListLabel);
    pIPAddressLayout->addWidget(m_pIPAddressEdit);

    QPushButton* pJoinGameBtn = new QPushButton(tr("Join Game"));

    pDlgBtnLayout->addStretch();
    pDlgBtnLayout->addWidget(pJoinGameBtn);

    pDlgLayout->addLayout(pPlayerNameEditLayout);
    pDlgLayout->addLayout(pIPAddressLayout);
    pDlgLayout->addStretch();
    pDlgLayout->addLayout(pDlgBtnLayout);

    setLayout(pDlgLayout);

    connect(pJoinGameBtn, SIGNAL(clicked()), this, SLOT(onBtnJoinGame()));
}

QString JoinGameDlg::getPlayerName()
{
    return m_pPlayerNameEdit->text();
}

QString JoinGameDlg::getHostServerIPAddress()
{
    return m_pIPAddressEdit->text();
}

void JoinGameDlg::onBtnJoinGame()
{
    emit joinGame();
}

void JoinGameDlg::closeEvent(QCloseEvent *closeEvent)
{
    emit cancelJoinGame();
}