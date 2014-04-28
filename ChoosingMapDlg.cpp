#include <QLayout>
#include <QLabel>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>

#include "ChoosingMapDlg.h"
#include "GameSetting.h"

ChoosingMapDlg::ChoosingMapDlg(QWidget *parent)
    : QDialog(parent),
      m_pMapList(NULL), m_pGameSetting(NULL)
{

}

ChoosingMapDlg::~ChoosingMapDlg()
{
    if(NULL != m_pGameSetting)
    {
        delete m_pGameSetting;
        m_pGameSetting = NULL;
    }
}

bool ChoosingMapDlg::initialize()
{
    bool bInitDlgSuccessed = true;

    QVBoxLayout* pDlgLayout = new QVBoxLayout;
    QHBoxLayout* pDlgBtnLayout = new QHBoxLayout;
    QHBoxLayout* pComboLayout = new QHBoxLayout;

    QLabel* pChooseLabel = new QLabel(tr("select a map to create a game"));
    m_pMapList = new QComboBox;
    pComboLayout->addWidget(pChooseLabel);
    pComboLayout->addWidget(m_pMapList);

    QPushButton* pCreateGameBtn = new QPushButton(tr("Create Game"));

    pDlgBtnLayout->addStretch();
    pDlgBtnLayout->addWidget(pCreateGameBtn);

    pDlgLayout->addLayout(pComboLayout);
    pDlgLayout->addStretch();
    pDlgLayout->addLayout(pDlgBtnLayout);

    setLayout(pDlgLayout);

    connect(pCreateGameBtn, SIGNAL(clicked()), this, SLOT(onBtnCreateGame()));

    return bInitDlgSuccessed;
}

bool ChoosingMapDlg::updateMapList(const QStringList& mapList)
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

QString ChoosingMapDlg::getCurrentMap()
{
    return m_pMapList->currentText();
}

void ChoosingMapDlg::closeEvent(QCloseEvent *closeEvent)
{
    emit cancelCreateGame();
}

void ChoosingMapDlg::onBtnCreateGame()
{
    emit createGame(getCurrentMap());
}