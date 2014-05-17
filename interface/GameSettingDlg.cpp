#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>

#include "GameSettingDlg.h"
#include "GameSetting.h"

GameSettingDlg::GameSettingDlg(QWidget *parent)
    : QDialog(parent),
      m_pPlayerNameEdit(NULL), m_pMapList(NULL), m_pGameSetting(NULL)
{

}

GameSettingDlg::~GameSettingDlg()
{
    delete m_pGameSetting;
    m_pGameSetting = NULL;
}

bool GameSettingDlg::initialize()
{
    bool bInitDlgSuccessed = true;

    QVBoxLayout* pDlgLayout = new QVBoxLayout;

    QHBoxLayout* pDlgBtnLayout = new QHBoxLayout;
    QHBoxLayout* pPlayerNameEditLayout = new QHBoxLayout;
    QHBoxLayout* pComboLayout = new QHBoxLayout;

    QLabel* pMapListLabel = new QLabel(tr("select a map to create a game"));
    m_pMapList = new QComboBox;
    pComboLayout->addWidget(pMapListLabel);
    pComboLayout->addWidget(m_pMapList);

    QLabel* pPlayerEditLabel = new QLabel(tr("Name: "));
    m_pPlayerNameEdit = new QLineEdit();
    pPlayerNameEditLayout->addWidget(pPlayerEditLabel);
    pPlayerNameEditLayout->addWidget(m_pPlayerNameEdit);
    pPlayerNameEditLayout->addStretch();

    QPushButton* pCreateGameBtn = new QPushButton(tr("Create Game"));

    pDlgBtnLayout->addStretch();
    pDlgBtnLayout->addWidget(pCreateGameBtn);

    pDlgLayout->addLayout(pPlayerNameEditLayout);
    pDlgLayout->addLayout(pComboLayout);
    pDlgLayout->addStretch();
    pDlgLayout->addLayout(pDlgBtnLayout);

    setLayout(pDlgLayout);

    connect(pCreateGameBtn, SIGNAL(clicked()), this, SLOT(onBtnCreateGame()));

    return bInitDlgSuccessed;
}

bool GameSettingDlg::updateMapList(const QStringList& mapList)
{
    bool bUpdateMapSuceessed = true;

    m_pMapList->clear();

    if(0 == mapList.size())
    {
        bUpdateMapSuceessed = false;
    }
    else
    {
        m_pMapList->addItems(mapList);
    }

    return bUpdateMapSuceessed;
}

QString GameSettingDlg::getCurrentMap()
{
    return m_pMapList->currentText();
}

QString GameSettingDlg::getPlayerName()
{
    return m_pPlayerNameEdit->text();
}

void GameSettingDlg::closeEvent(QCloseEvent *closeEvent)
{
    emit cancelCreateGame();
}

void GameSettingDlg::onBtnCreateGame()
{
    emit createGame();
}