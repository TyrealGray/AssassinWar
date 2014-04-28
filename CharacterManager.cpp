#include <QPainter>
#include <QTimer>

#include "CharacterManager.h"
#include "Character.h"

CharacterManager::CharacterManager()
    : m_pUpdateTimer(NULL),
      m_pGhostF(NULL)
{
    initUpdateTimer();
}

CharacterManager::~CharacterManager()
{
    if(NULL != m_pUpdateTimer)
    {
        delete m_pUpdateTimer;
        m_pUpdateTimer = NULL;
    }
}

void CharacterManager::addPlayer()
{
    m_pGhostF = new Character;
}

void CharacterManager::addCharacter()
{

}

void CharacterManager::addNpc()
{

}

void CharacterManager::setPlayerPos(const unsigned int &uiX, const unsigned int &uiY)
{
    m_pGhostF->goTo(uiX, uiY);
}

void CharacterManager::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pGhostF->render(painter, iOffsetX, iOffsetY);
}

unsigned int CharacterManager::getPlayerGridX()
{
    return m_pGhostF->getCurrentGridX();
}

unsigned int CharacterManager::getPlayerGridY()
{
    return m_pGhostF->getCurrentGridY();
}

void CharacterManager::initUpdateTimer()
{
    m_pUpdateTimer = new QTimer(this);
    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(updateAllCharacterPos()));
    m_pUpdateTimer->start(200);
}

void CharacterManager::updateAllCharacterPos()
{
    m_pGhostF->updatePosition();
}