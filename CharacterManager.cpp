#include <QPainter>

#include "CharacterManager.h"
#include "Character.h"

CharacterManager::CharacterManager()
    : m_pGhostF(NULL)
{
    m_pGhostF = new Character;
}

CharacterManager::~CharacterManager()
{

}

CharacterManager& CharacterManager::instance()
{
    static CharacterManager sCharacterManager;
    return sCharacterManager;
}

void CharacterManager::setGhostPos(const unsigned int &uiX, const unsigned int &uiY)
{
    m_pGhostF->goTo(uiX, uiY);
}

void CharacterManager::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pGhostF->render(painter, iOffsetX, iOffsetY);
}

unsigned int CharacterManager::getPlayerCharacterGridX()
{
    return m_pGhostF->getCurrentGridX();
}

unsigned int CharacterManager::getPlayerCharacterGridY()
{
    return m_pGhostF->getCurrentGridY();
}