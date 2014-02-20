#include "QPainter"

#include "CharacterManager.h"

CharacterManager::CharacterManager()
    : m_pGhostF(NULL),
      m_fX(-1.0),
      m_fY(-1.0)
{
    m_pGhostF = new QImage;
    m_pGhostF->load("./Resources/Character/Ghost-F.png");
}

CharacterManager::~CharacterManager()
{

}

CharacterManager& CharacterManager::instance()
{
    static CharacterManager sCharacterManager;
    return sCharacterManager;
}

void CharacterManager::setGhostPos(const float &fX, const float &fY)
{
    m_fX = fX;
    m_fY = fY;
}

void CharacterManager::drawAllCharacter(QPainter &painter)
{
    painter.drawImage(static_cast<int>(m_fX - 10), static_cast<int>(m_fY - 10) , (*m_pGhostF));
}